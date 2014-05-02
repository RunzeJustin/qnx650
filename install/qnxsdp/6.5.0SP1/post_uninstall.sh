#!/bin/sh

(
BASEDIR=$1
if test ! -r "$BASEDIR/host/linux/x86/usr/bin/mkxfs"; then
   rm -f "$BASEDIR/host/linux/x86/usr/bin/mketfs"
fi
if test ! -r "$BASEDIR/host/linux/x86/usr/bin/mkxfs"; then
   rm -f "$BASEDIR/host/linux/x86/usr/bin/mkefs"
fi
if test ! -r "$BASEDIR/host/linux/x86/usr/bin/mkxfs"; then
   rm -f "$BASEDIR/host/linux/x86/usr/bin/mkifs"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/bin/gunzip"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/bin/uncompress"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/bin/bzgrep"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/bin/bzfgrep"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/bin/bzip2"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/bin/bunzip2"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/bin/bzip2"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/bin/bzcat"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/bin/bzgrep"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/bin/bzegrep"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/bin/bzdiff"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/bin/bzcmp"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/bin/bzmore"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/bin/bzless"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/sbin/named"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/sbin/lwresd"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/sbin/named-checkzone"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/sbin/named-compilezone"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/../../lib/libc.so.3"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/ldqnx.so.2"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/libcrypto.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libcrypto.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/libbz2.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libbz2.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/libbacktrace.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libbacktrace.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/libssl.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libssl.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/libqdb_cldr.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libqdb_cldr.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/malloc_g/libmalloc.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/malloc_g/libmalloc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/libnbutil.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libnbutil.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/malloc_g/libmallocS.a"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libmalloc_gS.a"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/libham.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libham.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/libsqlite3.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libsqlite3.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/libqdb.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libqdb.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/libgf.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libgf.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/libAp.so.3"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libAp.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/libmalloc.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libmalloc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/libz.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libz.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/libcurl.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libcurl.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/malloc_g/libmalloc.so"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/libmalloc_g.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/usr/lib/librcheck.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/usr/lib/librcheck.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/lib/libcam.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/lib/libcam.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/lib/libhiddi.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/lib/libhiddi.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/lib/libc.so.3"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/lib/libc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/lib/libasound.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/lib/libasound.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/lib/libimg.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/lib/libimg.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/lib/libm.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/lib/libm.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/lib/libsocket.so.3"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/lib/libsocket.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/lib/libwlconfig.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/lib/libwlconfig.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/lib/libusbdi.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/lib/libusbdi.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle-v7/lib/libpps.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle-v7/lib/libpps.so"
fi
if test ! -r "$BASEDIR/target/qnx6/usr/include/mk/phapps.mk"; then
   rm -f "$BASEDIR/target/qnx6/usr/include/phapps.mk"
fi
if test ! -r "$BASEDIR/target/qnx6/usr/include/sys/md5.h"; then
   rm -f "$BASEDIR/target/qnx6/usr/include/md5.h"
fi
if test ! -r "$BASEDIR/target/qnx6/usr/include/mk/recurse.mk"; then
   rm -f "$BASEDIR/target/qnx6/usr/include/recurse.mk"
fi
if test ! -r "$BASEDIR/target/qnx6/usr/include/sys/queue.h"; then
   rm -f "$BASEDIR/target/qnx6/usr/include/queue.h"
fi
if test ! -r "$BASEDIR/target/qnx6/usr/include/sys/poll.h"; then
   rm -f "$BASEDIR/target/qnx6/usr/include/poll.h"
fi
if test ! -r "$BASEDIR/target/qnx6/usr/include/mk/ab.mk"; then
   rm -f "$BASEDIR/target/qnx6/usr/include/ab.mk"
fi
if test ! -r "$BASEDIR/target/qnx6/usr/include/mk/buildlist.mk"; then
   rm -f "$BASEDIR/target/qnx6/usr/include/buildlist.mk"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/bin/gunzip"; then
   rm -f "$BASEDIR/target/qnx6/armle/bin/uncompress"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/bin/bzgrep"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/bin/bzfgrep"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/bin/bzip2"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/bin/bunzip2"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/bin/bzip2"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/bin/bzcat"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/bin/bzgrep"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/bin/bzegrep"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/bin/bzdiff"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/bin/bzcmp"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/bin/bzmore"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/bin/bzless"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/sbin/named"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/sbin/lwresd"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/sbin/named-checkzone"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/sbin/named-compilezone"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/../../lib/libc.so.3"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/ldqnx.so.2"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/libcrypto.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libcrypto.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/libbz2.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libbz2.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/libbacktrace.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libbacktrace.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/libssl.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libssl.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/libqdb_cldr.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libqdb_cldr.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/malloc_g/libmalloc.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/malloc_g/libmalloc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/libnbutil.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libnbutil.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/malloc_g/libmallocS.a"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libmalloc_gS.a"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/libham.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libham.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/libsqlite3.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libsqlite3.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/libqdb.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libqdb.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/libgf.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libgf.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/libAp.so.3"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libAp.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/libmalloc.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libmalloc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/libz.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libz.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/libcurl.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libcurl.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/malloc_g/libmalloc.so"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/libmalloc_g.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/usr/lib/librcheck.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle/usr/lib/librcheck.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/lib/libcam.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle/lib/libcam.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/lib/libhiddi.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle/lib/libhiddi.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/lib/libc.so.3"; then
   rm -f "$BASEDIR/target/qnx6/armle/lib/libc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/lib/libasound.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle/lib/libasound.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/lib/libimg.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle/lib/libimg.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/lib/libm-vfp.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle/lib/libm-vfp.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/lib/libm.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle/lib/libm.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/lib/libsocket.so.3"; then
   rm -f "$BASEDIR/target/qnx6/armle/lib/libsocket.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/lib/libwlconfig.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle/lib/libwlconfig.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/lib/libusbdi.so.2"; then
   rm -f "$BASEDIR/target/qnx6/armle/lib/libusbdi.so"
fi
if test ! -r "$BASEDIR/target/qnx6/armle/lib/libpps.so.1"; then
   rm -f "$BASEDIR/target/qnx6/armle/lib/libpps.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/bin/gunzip"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/bin/uncompress"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/bin/bzgrep"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/bin/bzfgrep"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/bin/bzip2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/bin/bunzip2"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/bin/bzip2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/bin/bzcat"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/bin/bzgrep"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/bin/bzegrep"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/bin/bzdiff"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/bin/bzcmp"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/bin/bzmore"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/bin/bzless"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/sbin/named"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/sbin/lwresd"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/sbin/named-checkzone"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/sbin/named-compilezone"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/../../lib/libc.so.3"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/ldqnx.so.2"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/libcrypto.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libcrypto.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/libbz2.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libbz2.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/libbacktrace.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libbacktrace.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/libssl.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libssl.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/libqdb_cldr.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libqdb_cldr.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/malloc_g/libmalloc.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/malloc_g/libmalloc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/libnbutil.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libnbutil.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/malloc_g/libmallocS.a"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libmalloc_gS.a"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/libham.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libham.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/libsqlite3.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libsqlite3.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/libqdb.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libqdb.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/libgf.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libgf.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/libAp.so.3"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libAp.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/libmalloc.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libmalloc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/libz.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libz.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/libcurl.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libcurl.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/malloc_g/libmalloc.so"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/libmalloc_g.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/usr/lib/librcheck.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/usr/lib/librcheck.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/lib/libcam.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/lib/libcam.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/lib/libhiddi.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/lib/libhiddi.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/lib/libc.so.3"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/lib/libc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/lib/libasound.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/lib/libasound.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/lib/libimg.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/lib/libimg.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/lib/libm.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/lib/libm.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/lib/libsocket.so.3"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/lib/libsocket.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/lib/libwlconfig.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/lib/libwlconfig.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/lib/libusbdi.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/lib/libusbdi.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe/lib/libpps.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe/lib/libpps.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/bin/gunzip"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/bin/uncompress"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/bin/bzgrep"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/bin/bzfgrep"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/bin/bzip2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/bin/bunzip2"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/bin/bzip2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/bin/bzcat"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/bin/bzgrep"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/bin/bzegrep"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/bin/bzdiff"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/bin/bzcmp"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/bin/bzmore"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/bin/bzless"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/sbin/named"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/sbin/lwresd"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/sbin/named-checkzone"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/sbin/named-compilezone"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/../../lib/libc.so.3"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/ldqnx.so.2"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libcrypto.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libcrypto.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libbz2.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libbz2.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libbacktrace.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libbacktrace.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libssl.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libssl.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libqdb_cldr.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libqdb_cldr.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/malloc_g/libmalloc.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/malloc_g/libmalloc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libnbutil.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libnbutil.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/malloc_g/libmallocS.a"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libmalloc_gS.a"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libham.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libham.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libsqlite3.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libsqlite3.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libqdb.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libqdb.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libmalloc.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libmalloc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libz.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libz.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libcurl.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libcurl.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/malloc_g/libmalloc.so"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/libmalloc_g.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/librcheck.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/usr/lib/librcheck.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/lib/libcam.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/lib/libcam.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/lib/libhiddi.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/lib/libhiddi.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/lib/libc.so.3"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/lib/libc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/lib/libasound.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/lib/libasound.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/lib/libm.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/lib/libm.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/lib/libsocket.so.3"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/lib/libsocket.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/lib/libwlconfig.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/lib/libwlconfig.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/lib/libusbdi.so.2"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/lib/libusbdi.so"
fi
if test ! -r "$BASEDIR/target/qnx6/ppcbe-spe/lib/libpps.so.1"; then
   rm -f "$BASEDIR/target/qnx6/ppcbe-spe/lib/libpps.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/bin/gunzip"; then
   rm -f "$BASEDIR/target/qnx6/x86/bin/uncompress"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/bin/bzgrep"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/bin/bzfgrep"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/bin/bzip2"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/bin/bunzip2"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/bin/bzip2"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/bin/bzcat"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/bin/bzgrep"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/bin/bzegrep"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/bin/bzdiff"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/bin/bzcmp"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/bin/../../usr/photon/bin/inputtrap"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/bin/inputtrap"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/bin/bzmore"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/bin/bzless"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/sbin/named"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/sbin/lwresd"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/sbin/named-checkzone"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/sbin/named-compilezone"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/../../lib/libc.so.3"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/ldqnx.so.2"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/libcrypto.so.2"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libcrypto.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/libbz2.so.1"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libbz2.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/libbacktrace.so.1"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libbacktrace.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/libssl.so.2"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libssl.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/libqdb_cldr.so.1"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libqdb_cldr.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/malloc_g/libmalloc.so.2"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/malloc_g/libmalloc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/libnbutil.so.1"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libnbutil.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/malloc_g/libmallocS.a"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libmalloc_gS.a"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/libham.so.2"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libham.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/libsqlite3.so.1"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libsqlite3.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/libqdb.so.1"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libqdb.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/libgf.so.1"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libgf.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/libAp.so.3"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libAp.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/libmalloc.so.2"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libmalloc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/libz.so.2"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libz.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/libcurl.so.2"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libcurl.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/malloc_g/libmalloc.so"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/libmalloc_g.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/usr/lib/librcheck.so.1"; then
   rm -f "$BASEDIR/target/qnx6/x86/usr/lib/librcheck.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/lib/libcam.so.2"; then
   rm -f "$BASEDIR/target/qnx6/x86/lib/libcam.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/lib/libhiddi.so.1"; then
   rm -f "$BASEDIR/target/qnx6/x86/lib/libhiddi.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/lib/libc.so.3"; then
   rm -f "$BASEDIR/target/qnx6/x86/lib/libc.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/lib/libasound.so.2"; then
   rm -f "$BASEDIR/target/qnx6/x86/lib/libasound.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/lib/libimg.so.1"; then
   rm -f "$BASEDIR/target/qnx6/x86/lib/libimg.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/lib/libm.so.2"; then
   rm -f "$BASEDIR/target/qnx6/x86/lib/libm.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/lib/libsocket.so.3"; then
   rm -f "$BASEDIR/target/qnx6/x86/lib/libsocket.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/lib/libwlconfig.so.1"; then
   rm -f "$BASEDIR/target/qnx6/x86/lib/libwlconfig.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/lib/libusbdi.so.2"; then
   rm -f "$BASEDIR/target/qnx6/x86/lib/libusbdi.so"
fi
if test ! -r "$BASEDIR/target/qnx6/x86/lib/libpps.so.1"; then
   rm -f "$BASEDIR/target/qnx6/x86/lib/libpps.so"
fi
) >/tmp/qnx_del_link.log 2>&1
