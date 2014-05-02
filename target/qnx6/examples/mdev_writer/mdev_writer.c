#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <pthread.h>
#include <stdint.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/iomgr.h>
#include <sys/slog.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/mman.h>
#include <mm/mdev.h>

#ifdef __USAGE
%C -- mdev stream writer
#endif

#define WAV_CHUNKID      0x46464952
#define WAV_SUBCHUNK1ID  0x20746d66
#define WAV_SUBCHUNK2ID  0x61746164

#ifndef LOG_LEVEL
#define LOG_LEVEL   4
#endif

#undef LOG
#undef LOGV
#undef LOGD
#undef LOGI
#undef LOGW
#undef LOGE

#define LOG(level, fmt, ...)  ((level <= LOG_LEVEL) ? printf("stream-writer:%s: "fmt"\n", __func__, ##__VA_ARGS__) : (void)0);
#define LOGV(fmt, ...)      LOG(5, fmt, ##__VA_ARGS__)
#define LOGD(fmt, ...)      LOG(4, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...)      LOG(3, fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...)      LOG(2, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...)      LOG(1, fmt, ##__VA_ARGS__)

typedef struct {
    struct _pulse       phdr;
    mdev_pktheader_t    mhdr;
} mdev_msg_header_t;

typedef struct {
    uint32_t    chunk_id;      //Contains the letters "RIFF" in ASCII form  (0x52494646 big-endian form).
    uint32_t    chunk_size;
    uint32_t    format;
    uint32_t    subchunk1_id;  //Contains the letters "fmt "  (0x666d7420 big-endian form).
    uint32_t    subchunk1_size;
    uint16_t    audio_format;
    uint16_t    channels;
    uint32_t    sample_rate;
    uint32_t    byte_rate;
    uint16_t    block_align;
    uint16_t    bits_per_sample;
    uint32_t    subchunk2_id;   //Contains the letters "data"  (0x64617461 big-endian form).
    uint32_t    subchunk2_size;
} wave_header_t;

/* Global variables */
static bool g_strippts = false;
static bool g_repeatwrite = false;

FILE * open_wav(const char * url, wave_header_t * wavheader) {
    FILE * fp = fopen(url, "r");
    if (fp == NULL) {
        LOGE("cound no topen %s for read", url);
        return NULL;
    }

    if (fread(wavheader, sizeof(*wavheader), 1, fp) != 1) {
        LOGW("read wav file %s error", url);
        fclose(fp);
        return NULL;
    }
    //verify wave file header
    if (wavheader->chunk_id != WAV_CHUNKID || wavheader->subchunk1_id != WAV_SUBCHUNK1ID || wavheader->subchunk2_id
            != WAV_SUBCHUNK2ID) {
        LOGW("Invalid wave file.chunkid:0x%x sub chunk1id:0x%x sub chunk2id:0x%x",
                wavheader->chunk_id,
                wavheader->subchunk1_id,
                wavheader->subchunk2_id);
        fclose(fp);
        return NULL;
    }

    if (wavheader->byte_rate <= 0) {
        LOGW("Invalid wave file. byte rate :%d", wavheader->byte_rate);
        fclose(fp);
        return NULL;
    }
    LOGD("wave file %s open success.", url);
    LOGD("AudoFormat: %d NumChannels:%d SampleRate:%d ByteRate %d BlockAlign %d BitsPerSample:%d",
            wavheader->audio_format,
            wavheader->channels,
            wavheader->sample_rate,
            wavheader->byte_rate,
            wavheader->block_align,
            wavheader->bits_per_sample);

    LOGD("wave file pcm data size:%d", wavheader->subchunk2_size);
    return fp;
}

int write_wav_file(int devfd, const char * wavfilename, int pid) {

    int err = 0;
    wave_header_t wavhdr;
    FILE * fpwav = open_wav(wavfilename, &wavhdr);
    if (fpwav == NULL) {
        return -1;
    }

    //calculate duration in milliseconds
    int duration = (size_t) (((double) wavhdr.subchunk2_size) * 1000 / wavhdr.byte_rate);
    LOGI("wav %s duration %d", wavfilename, duration);

    mdev_msg_header_t * fbuf = (mdev_msg_header_t *) malloc(sizeof(*fbuf) + sizeof(mdev_format_t));
    mdev_format_t * fmt = (mdev_format_t *) (fbuf + 1);

    fbuf->phdr.type = 0;
    fbuf->phdr.subtype = 0;
    fbuf->mhdr.type = mdev_pkt_mktype(MDEV_PACKET_TYPE_FORMAT, pid);
    fbuf->mhdr.len = sizeof(*fmt);

    fmt->fourcc = MDEV_FOURCC('R','A','W','A');
    fmt->mtype = MDEV_MEDIA_AUDIO;
    fmt->audio.channels = wavhdr.channels;
    fmt->audio.duration = duration;
    fmt->audio.depth = wavhdr.bits_per_sample;
    fmt->audio.frame_rate = wavhdr.sample_rate;
    fmt->audio.scale = 1;

    LOGD("sending format packet.");
    if (MsgSend(devfd, fbuf, sizeof(*fbuf) + sizeof(mdev_format_t), NULL, 0) == -1) {
        LOGE("MsgSend error");
        free(fbuf);
        fclose(fpwav);
        return -1;
    }
    free(fbuf);

    //set buffer size to 20 milliseconds data
    int dur = 20000;

    int buffersize = wavhdr.byte_rate * (dur/1000) / 1000;
    LOGD("byterate(%d)buffer size(%d)", wavhdr.byte_rate, buffersize);
    mdev_msg_header_t * dbuf = (mdev_msg_header_t *) malloc(sizeof(*dbuf) + buffersize);
    dbuf->phdr.type = 0;
    dbuf->phdr.subtype = 0;
    dbuf->mhdr.type = mdev_pkt_mktype(MDEV_PACKET_TYPE_DATA, pid);
    dbuf->mhdr.len = buffersize;

    LOGD("sending audio data.");
    int pktcounter = 0;
    while (!feof(fpwav) && !err) {
        if ((dbuf->mhdr.len = fread(dbuf + 1, 1, buffersize, fpwav)) < 0) {
            LOGE("read wav file error.");
            err = -1;
            break;
        }
        do {
            if ((err = MsgSend_r(devfd, dbuf, sizeof(*dbuf) + dbuf->mhdr.len, NULL, 0)) == -EBUSY) {
                LOGV("server busy, retry...");
                usleep(dur/6);
            } else {
                if (err != 0) {
                    LOGE("MsgSend Error : %d", err);
                } else {
                   // LOGV("MsgSend success");
                    if (++pktcounter % 100 == 0) {
                        LOGD("sent %d packets", pktcounter);
                    }
                }
                //usleep(dur/8);
                break;
            }
        } while (1);
    }

    free(dbuf);
    fclose(fpwav);
    return err;
}

int write_raw_file(int devfd, const char * fname) {
    FILE * fp = fopen(fname, "rb");
    if (fp == NULL) {
        LOGE("Could not open %s for read", fname);
        return -1;
    }

    mdev_msg_header_t msghdr = { { 0 } };
    mdev_pktheader_t *mhdr = &(msghdr.mhdr);
    int err = 0;
    int pktcounter = 0;
    uint8_t *buf = NULL;
    size_t buf_sz = 0;
    enum {
        IOV_HEADER = 0,
        IOV_DATA,
        IOV_MAX
    };
    iov_t iov[IOV_MAX];
    while(err == 0 && !feof(fp)) {
        fread(mhdr, 1, sizeof(*mhdr), fp);

        if (mhdr->len > 1024*1024*10) {
            LOGW("Packet too long, corrupted file");
            break;
        }

       if (mhdr->len > buf_sz) {
           free(buf);
           if ((buf = malloc(mhdr->len)) == NULL) {
               err = errno;
               LOGE("malloc(%u) failed, error %d.", mhdr->len, err);
               break;
           }
           buf_sz = mhdr->len;
       }
       if (fread(buf, 1, mhdr->len, fp) < 0) {
           err = errno;
           LOGE("fread(1, %u) failed, error %d.", mhdr->len, err);
           break;
       }
       SETIOV( &iov[IOV_HEADER], &msghdr, sizeof(msghdr) );
       SETIOV( &iov[IOV_DATA]  , buf    , mhdr->len      );

       if (mdev_pkt_type(mhdr) == MDEV_PACKET_TYPE_FORMAT) {
            LOGD("mhdr.type = %d len = %d", mhdr->type, mhdr->len);
            mdev_format_t * fmt = (mdev_format_t*) buf;
            LOGI("  FourCC: %-4.4s", (char *)&(fmt->fourcc));
            LOGI("  MediaType: %d", fmt->mtype);
            if ((fmt->mtype & MDEV_MEDIA_AUDIO)) {
                LOGI("  Channels: %d", fmt->audio.channels);
                LOGI("  Duration: %d", fmt->audio.duration);
                LOGI("  Sample rate: %d", fmt->audio.frame_rate);
                LOGI("  Bits per sample: %d", fmt->audio.depth);
            }
       }

       if (g_strippts) {
           if (mdev_pkt_type(mhdr) == MDEV_PACKET_TYPE_OPTIONFLAGS) {
               uint32_t *option = (uint32_t *)buf;
               *option &= ~(MDEV_OPTIONFLAGS_ABSPTS);
               if (*option == 0) {
                   LOGI("Skipping optionflags packet because flags are now zero.");
                   continue;
               }
           } else if (mdev_pkt_type(mhdr) == MDEV_PACKET_TYPE_PTSDATA) {
               mhdr->type = MDEV_PACKET_TYPE_DATA;
#define PTS_SIZE (8)
               mhdr->len -= PTS_SIZE;
               SETIOV( &iov[IOV_DATA], buf + PTS_SIZE, mhdr->len );
           }
       }

       do {
               if ((err = MsgSendvs_r(devfd, iov, IOV_MAX, NULL, 0)) == -EBUSY) {
                   LOGV("server busy, retry...");
                   usleep(1000 * 200);
               } else {
                   if (err != 0) {
                       LOGE("MsgSend Error : %d", err);
                   } else {
                       LOGV("MsgSend success");
                       if (++pktcounter % 10 == 0) {
                           LOGD("sent %d packets", pktcounter);
                       }
                   }
                   break;
               }
        } while (1);

    }

    free(buf);
    fclose(fp);
    return err;
}
//
// Find the first occurrence of the byte string s in byte string l.
void *  memmem(const void *l, size_t l_len, const void *s, size_t s_len) {

    const char *cl = (const char *)l;
    const char *cs = (const char *)s;

    if (l_len == 0 || s_len == 0 || l_len < s_len) {
        return NULL;
    }

    if (s_len == 1) {
        return memchr(l, (int)*cs, l_len);
    }

    char *cur, *last;
    last = (char *)cl + l_len - s_len;
    for (cur = (char *)cl; cur <= last; cur++) {
        if (cur[0] == cs[0] && memcmp(cur + 1, cs + 1, s_len - 1) == 0) {
            return cur;
        }
    }
    return NULL;
}
static int mdev_send_data2(int coid, uint32_t type, void * data1, size_t len1, void * data2, size_t len2) {
    mdev_msg_header_t      msg;
    iov_t               iov_to[3];
    int                 rc, retry = 100;

    int iovn = 2;
    // Send the mdev data packet
    msg.phdr.type = 0;
    msg.phdr.subtype = 0;
    msg.mhdr.type = type;
    msg.mhdr.len = len1+len2;
    SETIOV(&iov_to[0], &msg, sizeof(msg));
    SETIOV(&iov_to[1], data1, len1);
    SETIOV(&iov_to[2], data2, len2);
    if (data2 && len2) {
        iovn++;
    }
    do {
        rc = MsgSendvs_r(coid, iov_to, iovn, NULL, 0);
        if (rc == -EBUSY) {
            // LOGW("Failed to mdev data packet size=%d errno=%d str=%s\n", len1 + len2, errno, strerror(errno));
            delay(10);
        } else {
            break;
        }
    } while (retry--);

    return rc;
}

static size_t get_file_size(const char * filename) {
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

extern void draw_uyvy_img(uint8_t * dest, uint32_t * canvas, int w, int h, int stride);
static int write_uyvy_video(int devfd, int width, int heigh, int pid) {

    LOGD("generate yuv video frame width(%d) height(%d)", width, heigh);
    int depth = 16;
    int err = 0;
    mdev_format_t fmt;
    fmt.fourcc = MDEV_FOURCC('Y','V','Y','U');
    //if no PTS before each frame, this frame_rate would take effect.
    fmt.video.frame_rate=30;
    fmt.video.depth=depth;
    fmt.video.width=width;
    fmt.video.height=heigh;

    //work on vmware
    int32_t size = width * heigh * 2;
    uint32_t * canvas = calloc(1, width * heigh * 4);
    uint8_t * outbuf = calloc(1, size);

    int32_t frames = 0;
    LOGD("sending format packet.");
    uint64_t pts = 0;
    mdev_send_data2(devfd, mdev_pkt_mktype(MDEV_PACKET_TYPE_FORMAT, pid), &fmt, sizeof(fmt), NULL, 0);
    while(1) {
        draw_uyvy_img(outbuf, canvas, width, heigh, width * 2);
#if 1
        if ((err = mdev_send_data2(devfd, mdev_pkt_mktype(MDEV_PACKET_TYPE_DATA, pid), outbuf, size, NULL, 0)) < 0) {
                 LOGE("send error, break");
                 break;
             }
#else
        //enable this if want to send PTSDATA
        if ((err = mdev_send_data2(devfd, mdev_pkt_mktype(MDEV_PACKET_TYPE_PTSDATA, pid), &pts, sizeof(pts), outbuf, size)) < 0) {
            LOGE("send error, break");
            break;
        }
#endif
        if (frames++%fmt.video.frame_rate == 0) {
            LOGD("sent %d frames", frames);
        }
        pts += (1000000LL)/(fmt.video.frame_rate);
    }

    free(outbuf);
    free(canvas);
    return err;
}

static int write_aac_file(int fd, const char * fname, int pid) {
    FILE * fp = fopen(fname, "r");
    if (fp == NULL) {
        LOGI("open %s error", fname);
        return -1;
    }
    mdev_format_t fmt;
     fmt.fourcc = MDEV_FOURCC('M','4','A','C');
     fmt.audio.channels = 2;
     fmt.audio.duration = 0;
     fmt.audio.depth = 16;
     fmt.audio.frame_rate = 44100;
     fmt.audio.scale = 1;
     LOGD("sending format packet.");
     mdev_send_data2(fd, mdev_pkt_mktype(MDEV_PACKET_TYPE_FORMAT, pid), &fmt, sizeof(fmt), NULL, 0);

     unsigned char buf[1024 * 2];
     int nbytes;
     int err = 0;
     int plen;
     while(!feof(fp)) {
         fread(&plen, sizeof(plen), 1, fp);
         if(plen > sizeof(buf)) {
             LOGE("corrupted file plen = %d", plen);
             err= -1;
             break;
         }
         if (plen > 0) {
         nbytes = fread(buf, 1, plen, fp);
         if ((err = mdev_send_data2(fd, mdev_pkt_mktype(MDEV_PACKET_TYPE_DATA, pid), buf, nbytes, NULL, 0)) < 0) {
             LOGE("send error");
             break;
         }
         }
     }

     fclose(fp);
     return err;
}
static int write_h264_file(int devfd, const char * fname, int pid) {
    int fd = open(fname, O_RDONLY, 0);
    if (fd < 0)  {
        LOGI("open error");
    }
    size_t fsize = get_file_size(fname);
    unsigned char * filemem = mmap(0, fsize, PROT_READ, MAP_PRIVATE|MAP_FILE, fd, 0);
    if (filemem == MAP_FAILED) {
        LOGE("map failed.");
        close(fd);
        return -1;
    }
    const unsigned char sync[] = {0,0,0,1};
    unsigned char * framestart = memmem(filemem, fsize, sync, sizeof(sync));
    if (framestart == NULL) {
        LOGI("could not find sync code, not a H264 Annex B file");
        munmap(filemem, fsize);
        close(fd);
        return -1;
    }


    mdev_format_t fmt;
    fmt.fourcc = MDEV_FOURCC('H','2','6','4');
    //if no PTS before each frame, this frame_rate would take effect.
    fmt.video.frame_rate=24;
    fmt.video.depth=16;
    fmt.video.width=1280;
    fmt.video.height=720;
    LOGD("sending format packet.");
    mdev_send_data2(devfd, mdev_pkt_mktype(MDEV_PACKET_TYPE_FORMAT, pid), &fmt, sizeof(fmt), NULL, 0);

    size_t remains = fsize - (framestart - filemem);

    int err = 0;
    uint64_t pts = 0;
    //int fcount = 0;
    while(remains > 0) {
        unsigned char * next = memmem(framestart + sizeof(sync), remains - sizeof(sync), sync, sizeof(sync));
        size_t sendsize = 0;
         if (next && pts == 0) {
            //send 2 frames first time
            next = memmem(next + sizeof(sync), remains - sizeof(sync) - (next - framestart), sync, sizeof(sync));
        }
        
        if (next) {
            sendsize = next - framestart;
        } else {
            sendsize = remains;
        }
        //send data
#if 1
        if ((err = mdev_send_data2(devfd, mdev_pkt_mktype(MDEV_PACKET_TYPE_DATA, pid), framestart, sendsize, NULL, NULL)) < 0) {
            LOGE("send error");
            break;
        }
#else
        if ((err=mdev_send_data2(devfd, mdev_pkt_mktype(MDEV_PACKET_TYPE_PTSDATA, pid), &pts, sizeof(pts), framestart, sendsize)) < 0) {
            LOGE("send error");
            break;
        }
#endif
        pts += (1000000LL/50);  //simulate 16 FPS
        framestart = next;
        remains -= sendsize;
    }


    munmap(filemem, fsize);
    close(fd);
    return err;

}
int write_one_file(int fd, const char * fname, int pid) {
    const char * p;
    if (strnicmp(fname, "dummy.yuv", 9) == 0) {
        int width = 800, height = 600;
        char * par = strchr(fname, '?');
        if (par) {
            char * p;
            if ((p = strstr(par, "width="))) {
                width = atoi(p + 6);
            }
            if ((p = strstr(par, "height="))) {
                height = atoi(p+7);
            }
        }
        return write_uyvy_video(fd, width, height, pid);
    }
    if ((p = strstr(fname, ".wav")) && strlen(p) == 4) {
        return write_wav_file(fd, fname, pid);
    } else if ((p = strstr(fname, ".h264")) && strlen(p) == 5) {
        return write_h264_file(fd, fname, pid);
    } else if ((p = strstr(fname, ".aac")) && strlen(p) == 4) {
        return write_aac_file(fd, fname, pid);
    }
    return write_raw_file(fd, fname);
}

typedef struct {
    int outfd;
    int pid;
    const char * infn;
}muxwrite_ctx_t;

int stop = 0;
void * thread_func(void * arg) {
    muxwrite_ctx_t * ctx = (muxwrite_ctx_t *)arg;
    while(!stop) {
        if ((write_one_file(ctx->outfd, ctx->infn, ctx->pid) < 0) || (!g_repeatwrite))
            break;
    }
    return NULL;
}

static void printusage(void) {
    printf("Usage: mdev-writer [opts] mdev_device input_file1 [input_file2]\n");
    printf("Opts:\n");
    printf("    -l  Repeat writing of input file\n");
    printf("    -S  Strip PTS data (from raw mdev input stream)\n");
    printf("Examples:\n");
    printf("    mdev-writer /dev/name/local/mdev test.wav\n");
    printf("    mdev-writer /dev/name/local/mdev audio.wav video.h264\n");
    printf("    mdev-writer /dev/name/local/mdev audio.wav DUMMY.yuv\n");
    printf("                DUMMY.yuv means mdev-writer generate yuv video data\n");
}

int main(int argc, char * argv[]) {
    int c;
    int fd;
    const char *name, *fn1, *fn2;

    while ((c = getopt(argc, argv, "lS")) != -1) {
        switch (c) {
        case 'l':
            g_repeatwrite = true;
        case 'S':
            g_strippts = true;
            break;
        case '?':
        default:
            break;
        }
    }

    if (((name = argv[optind++]) == NULL) || ((fn1 = argv[optind++]) == NULL)) {
        printusage();
        return 0;
    }
    fn2 = argv[optind++];

    if ((fd = name_open(name, NULL)) == -1) {
        LOGE("Could not open %s", name);
        return -1;
    }

    pthread_t tid = -1;
    if (fn2 != NULL) {
        muxwrite_ctx_t arg = {fd, 1, fn2};
        //write video in another thread
        if ((errno = pthread_create(&tid, NULL, thread_func, &arg)) != EOK) {
            LOGE("Error creating thread, error %d.", errno);
            return -1;
        }
    }

    do {
        if (write_one_file(fd, fn1, 0) < 0) {
            break;
        }
        LOGI("Finished writing file %s.", fn1);
    } while (g_repeatwrite);

    if (tid != -1) {
        stop = 1;
        pthread_join(tid, NULL);
    }
    name_close(fd);
    return 0;
}

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mmedia/streamers/mdev_streamer/mdev_writer/mdev_writer.c $ $Rev: 736007 $")
#endif
