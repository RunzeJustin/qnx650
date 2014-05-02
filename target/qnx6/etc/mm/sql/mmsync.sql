BEGIN EXCLUSIVE;

--
-- Set SQLite's auto-vacuum mode
--
-- Enables auto-vacuuming of the database on every transaction commit.
-- See <http://www.sqlite.org/pragma.html#pragma_auto_vacuum> for more information.
PRAGMA auto_vacuum=full;

-- *******************************************************************************
-- *******************************************************************************
-- @table _mmsync_info_
--
-- _mmsync_info_ contains a schema version number to help mm-sync identify the
-- schema version.  It may be extended in the future to include further schema-
-- related information for mm-sync.
--
-- @field version      mm-sync schema version
-- *******************************************************************************
-- *******************************************************************************
CREATE TABLE _mmsync_info_ (
      version INTEGER NOT NULL
);
INSERT INTO _mmsync_info_(version) VALUES(2000);


-- *******************************************************************************
-- *******************************************************************************
-- @table mediastore_metadata
--
-- mediastore_metadata provides access to information about the mediastore synced
-- to this database.  It is useful to mm-sync clients to build queries using the
-- mountpath, or to query the synchronizer used.
--
-- @field syncflags  Sync passes that have been completed on this mediastore.
-- @field last_sync  The system timestamp of the last sync operation.
-- @field mssname    The short name of the MSS used to sync the mediastore.
-- @field name       The name of this mediastore from the mss.
-- @field mountpath  The mountpath of the last (or active) sync operation.
-- *******************************************************************************
-- *******************************************************************************
CREATE TABLE mediastore_metadata (
      syncflags   INTEGER DEFAULT 0 NOT NULL,
      last_sync   INTEGER DEFAULT 0 NOT NULL,
      mssname     TEXT DEFAULT NULL,
      name        TEXT DEFAULT NULL,
      mountpath   TEXT NOT NULL
);


-- *******************************************************************************
-- *******************************************************************************
-- @table folders
--
-- The folders table stores the path of files found on media and can be used to
-- hierarchically find folders.
--
-- @field folderid    The folder ID for the folder.
-- @field parentid    The parent folder for this folder.  Set to 0 if there is no
--                    parent folder. 
-- @field synced      If this field is set to 1, the folder has been synchronized
--                    during the first synchronization pass.
-- @field filecount   The number of files in the folder.
-- @field playlistcount The number of playlists in the folder.
-- @field foldercount The number of subfolders in the folder.
-- @field last_sync   Reserved for the time (in nanoseconds from the reference) of
--                    the last synchronization attempt on the mediastore.
-- @field folderflags Flags providing more information about this folder.
-- @field foldername  The name of the folder (for example, <fname>Rolling Stones</fname>).
-- @field basepath    The full path of the folder  (for example,
--                    <fname>Music/Rolling Stones</fname>).
-- @field hash        For internal use only.
-- @field collisions  For internal use only.
-- @field collision_names For internal use only.
-- *******************************************************************************
-- *******************************************************************************
CREATE TABLE folders (
      folderid          INTEGER PRIMARY KEY AUTOINCREMENT,
      parentid          INTEGER DEFAULT 0 NOT NULL,
      synced            INTEGER DEFAULT 0 NOT NULL,
      filecount         INTEGER DEFAULT 0 NOT NULL,
      playlistcount     INTEGER DEFAULT 0 NOT NULL,
      foldercount       INTEGER DEFAULT 0 NOT NULL,
      last_sync         INTEGER DEFAULT 0 NOT NULL,
      folderflags       INTEGER DEFAULT 0 NOT NULL,
      foldername        TEXT NOT NULL,
      basepath          TEXT NOT NULL,
      hash              BLOB,
      collisions        BLOB,
      collision_names   BLOB
);


-- *******************************************************************************
-- *******************************************************************************
-- @table files
--
-- The files table defines the media library used by mm-sync.  Each entry in this
-- table is a media track that can be used to build track sessions and playlists.
--
-- @field fid              The file ID (fid) for the media track.
-- @field folderid         The path in the mediastore where the track is located.
-- @field ftype            The type of the media track, which corresponds to the 
--                         FTYPE_* types defined in <mmsync/interface.h>:
--                          * 0 = unknown
--                          * 1 = audio
--                          * 2 = video
--                          * 3 = (reserved)
--                          * 4 = photo
-- @field accurate         Indicates if the metadata for the track is known to be 
--                         accurate.
-- @field last_sync        The time (in nanoseconds from the reference) of the
--                         last metadata synchronization attempt for the track.
-- @field size             The size of the track, in bytes.
-- @field date_added       The date the track entry was added to the files
--                         table.
-- @field date_modified    The date the track entry was modified in the files
--                         table.
-- @field filename         The file name of the media track.
-- *******************************************************************************
-- *******************************************************************************
CREATE TABLE files (
      fid              INTEGER PRIMARY KEY AUTOINCREMENT,
      folderid         INTEGER DEFAULT 0 NOT NULL REFERENCES folders,
      ftype            INTEGER DEFAULT 0 NOT NULL,
      accurate         INTEGER DEFAULT 0 NOT NULL,
      last_sync        INTEGER DEFAULT 0 NOT NULL,
      size             INTEGER DEFAULT 0 NOT NULL,
      date_added       INTEGER DEFAULT 0 NOT NULL,
      date_modified    INTEGER DEFAULT 0 NOT NULL,
      filename         TEXT DEFAULT '' NOT NULL
);


-- *******************************************************************************
-- *******************************************************************************
-- @table audio_metadata
--
-- The audio_metadata contains metadata for audio files (files with FTYPE_AUDIO in
-- the default configuration).  Only files with an ftype configured to put some
-- metadata in this table will have an entry in this table.  Files are referenced
-- from the files table by the fid column.
--
-- @field fid              The file ID (fid) for the media track.
-- @field artist_id        The ID of the track artist.
-- @field album_id         The ID of the track album.
-- @field genre_id         The ID of the track genre.
-- @field year             The year of the track.
-- @field disc             The disc number of the content.
-- @field track            The track number on the album.
-- @field rating           The rating (0 = unknown, 1 = worst, 255 = best). Format
--                         specific rating is scaled to 1 - 255 range, for example
--                         1 stars = 60, 2 starts = 125, ..., 5 starts = 255).
-- @field bitrate          The track bitrate in bits per second.
-- @field samplerate       The sampling rate, in hertz, of the audio stream.
-- @field protected        Indicates if there is DRM on the track
-- @field duration         The track length, in milliseconds.
-- @field description      An arbitrary text description of the track.
-- @field fourcc           The fourcc character code of the track.
-- @field title            The track title.
-- *******************************************************************************
-- *******************************************************************************
CREATE TABLE audio_metadata (
      fid              INTEGER PRIMARY KEY NOT NULL REFERENCES files,
      artist_id        INTEGER DEFAULT 1 NOT NULL REFERENCES artists,
      album_id         INTEGER DEFAULT 1 NOT NULL REFERENCES albums,
      genre_id         INTEGER DEFAULT 1 NOT NULL REFERENCES genres,
      year             INTEGER DEFAULT 0 NOT NULL,
      disc             INTEGER DEFAULT 0 NOT NULL,
      track            INTEGER DEFAULT 0 NOT NULL,
      rating           INTEGER DEFAULT 0 NOT NULL,
      bitrate          INTEGER DEFAULT 0 NOT NULL,
      samplerate       INTEGER DEFAULT 0 NOT NULL,
      protected        INTEGER DEFAULT 0 NOT NULL,
      duration         INTEGER DEFAULT 0 NOT NULL,
      description      TEXT DEFAULT '' NOT NULL,
      compilation      INTEGER DEFAULT 0 NOT NULL,
      fourcc           TEXT DEFAULT '' NOT NULL,
      title            TEXT DEFAULT NULL
);


-- *******************************************************************************
-- *******************************************************************************
-- @table video_metadata
--
-- The video_metadata contains metadata for video files (files with FTYPE_VIDEO in
-- the default configuration).  Only files with an ftype configured to put some
-- metadata in this table will have an entry in this table.  Files are referenced
-- from the files table by the fid column.
--
-- @field fid              The file ID (fid) for the media track.
-- @field artist_id        The ID of the track artist.
-- @field genre_id         The ID of the track genre.
-- @field year             The year of the track.
-- @field width            The width of the video in pixels.
-- @field height           The height of the video in pixels.
-- @field rating           The rating (0 = unknown, 1 = worst, 255 = best). Format
--                         specific rating is scaled to 1 - 255 range, for example
--                         1 stars = 60, 2 starts = 125, ..., 5 starts = 255).
-- @field audio_bitrate    The combined audio/video stream bitrate in bits per second.
-- @field audio_samplerate The video frames per second
-- @field protected        Indicates if there is DRM on the track
-- @field duration         The track length, in milliseconds.
-- @field description      An arbitrary text description of the track.
-- @field audio_fourcc     The fourcc character code of the first audio track.
-- @field video_fourcc     The fourcc character code of the first video track.
-- @field title            The track title.
-- *******************************************************************************
-- *******************************************************************************
CREATE TABLE video_metadata (
      fid              INTEGER PRIMARY KEY NOT NULL REFERENCES files,
      artist_id        INTEGER DEFAULT 1 NOT NULL REFERENCES artists,
      genre_id         INTEGER DEFAULT 1 NOT NULL REFERENCES genres,
      year             INTEGER DEFAULT 0 NOT NULL,
      width            INTEGER DEFAULT 0 NOT NULL,
      height           INTEGER DEFAULT 0 NOT NULL,
      rating           INTEGER DEFAULT 0 NOT NULL,
      audio_bitrate    INTEGER DEFAULT 0 NOT NULL,
      audio_samplerate INTEGER DEFAULT 0 NOT NULL,
      protected        INTEGER DEFAULT 0 NOT NULL,
      duration         INTEGER DEFAULT 0 NOT NULL,
      description      TEXT DEFAULT '' NOT NULL,
      audio_fourcc     TEXT DEFAULT '' NOT NULL,
      video_fourcc     TEXT DEFAULT '' NOT NULL,
      title            TEXT DEFAULT NULL
);


-- *******************************************************************************
-- *******************************************************************************
-- @table photo_metadata
--
-- The photo_metadata table contains image metadata including EXIF metadata found
-- by mm-sync for image files (files with FTYPE_PHOTO in the default
-- configuration).  Only files with an ftype configured to put some metadata in
-- this table will have an entry in this table.  Files are referenced from the
-- files table by the fid column.
--
-- @field fid              The file ID (fid) for the media track.
-- @field latitude         The photo location's latitude.
-- @field longitude        The photo location's longitude.
-- @field width            The number of columns of image data.
-- @field height           The number of rows of image data.
-- @field orientation      The image orientation.
-- @field shutter          The shutter speed.
-- @field aperture         The lens aperture.
-- @field focal_length     The lens focal length.
-- @field iso              The film speed.
-- @field description      An arbitrary text description of the image.
-- @field date_original    The original date and timestamp from the image file.
-- @field keywords         Keywords associated with the image.
-- *******************************************************************************
-- *******************************************************************************
CREATE TABLE photo_metadata (
      fid              INTEGER PRIMARY KEY NOT NULL REFERENCES files,
      latitude         TEXT DEFAULT '' NOT NULL,
      longitude        TEXT DEFAULT '' NOT NULL,
      width            INTEGER DEFAULT 0 NOT NULL,
      height           INTEGER DEFAULT 0 NOT NULL,
      orientation      TEXT DEFAULT '' NOT NULL,
      shutter          TEXT DEFAULT '' NOT NULL,
      aperture         TEXT DEFAULT '' NOT NULL,
      focal_length     TEXT DEFAULT '' NOT NULL,
      iso              INTEGER DEFAULT 0 NOT NULL,
      description      TEXT DEFAULT '' NOT NULL,
      date_original    TEXT DEFAULT '' NOT NULL,
      keywords         TEXT DEFAULT '' NOT NULL
);


-- *******************************************************************************
-- *******************************************************************************
--
-- Metadata support tables
--
-- *******************************************************************************
-- *******************************************************************************
CREATE TABLE genres (
      genre_id         INTEGER PRIMARY KEY AUTOINCREMENT,
      genre            TEXT
);
CREATE INDEX genres_index_genre on genres(genre);

CREATE TABLE artists (
      artist_id        INTEGER PRIMARY KEY AUTOINCREMENT,
      artist           TEXT
);
CREATE INDEX artists_index_artist on artists(artist);

CREATE TABLE albums (
      album_id         INTEGER PRIMARY KEY AUTOINCREMENT,
      album            TEXT
);
CREATE INDEX albums_index_album on albums(album);


-- *******************************************************************************
-- *******************************************************************************
-- @table playlists
--
-- The playlists table holds playlists that your application can convert into
-- track sessions and play.  A playlist is a collection of media tracks.
--
-- @field plid             The playlist ID.
-- @field ownership        Indicates who owns this playlist:
--                          * 0 = owned by mm-sync
--                          * 1 = owned by the device
--                          * 2 = owned by the user
-- @field folderid         The ID of the folder that the playlist is in.
-- @field mode             The playlist mode:
--                          * 0 = library mode
--                          * 1 = generated mode
-- @field date_modified    The date this playlist was last modified.
-- @field accurate         If this field is set to 1, the playlist is accurate.
-- @field last_sync        The time (in nanoseconds from the reference) of the
--                         last playlist (pass 3) synchronization attempt for the
--                         playlist.
-- @field size             The size of the playlist file on the device.
-- @field signature        md5 hash of the playlist.
-- @field filename         If the playlist points to a device, the filename of the
--                         playlist on the device.  This name is a path relative to 
--                         the basepath of the folder.
-- @field name             The playlist name.
-- @field seed_data        Used by playlist generators (i.e. mode = 1)
-- @field lang_code        Language code used for case insensitive matching.
-- *******************************************************************************
-- *******************************************************************************
CREATE TABLE playlists (
      plid             INTEGER PRIMARY KEY AUTOINCREMENT,
      ownership        INTEGER DEFAULT 0 NOT NULL,
      folderid         INTEGER DEFAULT 0 NOT NULL REFERENCES folders,
      mode             INTEGER DEFAULT 0 NOT NULL,
      date_modified    INTEGER DEFAULT 0 NOT NULL,
      accurate         INTEGER DEFAULT 0 NOT NULL,
      last_sync        INTEGER DEFAULT 0 NOT NULL,
      size             INTEGER DEFAULT 0 NOT NULL,
      signature        TEXT DEFAULT '0' NOT NULL,
      filename         TEXT DEFAULT '' NOT NULL,
      name             TEXT NOT NULL,
      seed_data        TEXT,
      lang_code        TEXT DEFAULT 'en_CA' NOT NULL
);


-- *******************************************************************************
-- *******************************************************************************
-- @table playlist_entries
--
-- The playlist_entries table is available for storing any linear created
-- playlists.
--
-- @field plid          The ID of the playlist to which this track belongs.
-- @field fid           The track file ID (fid).
-- @field oid           An order identifier.  This can be used to order the
--                      playlist entries in the original playlist order.
-- @field unresolved_entry_text  An entry from the playlist that could not be
--                               resolved, but that matches the configured regex.
-- *******************************************************************************
-- *******************************************************************************
CREATE TABLE playlist_entries (
      oid                   INTEGER PRIMARY KEY AUTOINCREMENT,
      plid                  INTEGER NOT NULL REFERENCES playlists,
      fid                   INTEGER NOT NULL REFERENCES files,
      unresolved_entry_text TEXT DEFAULT NULL
);


-- *******************************************************************************
-- *******************************************************************************
-- @table ext_db_sync_state
--
-- The <fname>ext_db_sync_state</fname> table contains persistent state information for 
-- all extern DBs that must stay in sync with the mm-sync database.
-- @field uniquedbid       Unique identifier to each plugin so it can differentiate
--                         its state from that of another plugin.
-- @field data             The state data of the external DB
-- *******************************************************************************
-- *******************************************************************************
CREATE TABLE ext_db_sync_state(
      unique_db_id  TEXT NOT NULL,
      data          BLOB NOT NULL
);


-- *******************************************************************************
-- *******************************************************************************
--                         @table db_sync
-- The <fname>db_sync</fname> table is used by the generic handler for external
-- database synchronization plugins. It should be considered private to the mm-sync.
--
-- @field fid           The ID of a library table entry that synchronizers
--                      have been told about. (<var>fid</var>).
-- @field last_sync     The internal timestamp value when the external database
--                      synchronizers were last told about this file.
-- *******************************************************************************
-- *******************************************************************************
CREATE TABLE db_sync (
      fid           INTEGER NOT NULL REFERENCES files,
      last_sync     INTEGER DEFAULT 0 NOT NULL
);


-- *******************************************************************************
-- *******************************************************************************
--                                 INDEXES
--
-- Below are examples of indexes. You should remove indexes that you do not use,
-- and add indexes that you do use. Performance can be greatly increased when
-- reading from tables if the columns that are being used for WHERE and ORDER BY
-- have indexes.  PRIMARY KEY columns do not need an index created on them.
-- However, be warned:
-- 1/ Adding indices slows down table insertion, and may significantly increase
--    synchronization times.
-- 2/ The presence of excessive indices has even been observed to increase
--    lookup times.
-- Therefore, the recommendation is to use indices sparingly and carefully.
-- *******************************************************************************
-- *******************************************************************************

-- This helps first pass resync (bfsrecurse)
CREATE INDEX folders_index_parentid ON folders(parentid);


-- *****************
-- Required TRIGGERS
-- *****************
--
---- Metadata custom triggers --
CREATE TRIGGER audio_metadata_delete AFTER DELETE ON files WHEN OLD.ftype=1
   BEGIN
      DELETE FROM audio_metadata WHERE fid=OLD.fid;
   END;

CREATE TRIGGER video_metadata_delete AFTER DELETE ON files WHEN OLD.ftype=2
   BEGIN
      DELETE FROM video_metadata WHERE fid=OLD.fid;
   END;

CREATE TRIGGER photo_metadata_delete AFTER DELETE ON files WHEN OLD.ftype=4
   BEGIN
      DELETE FROM photo_metadata WHERE fid=OLD.fid;
   END;

-- *****************
-- Optional TRIGGERS
-- *****************
--
---- Files Custom Triggers
--CREATE TRIGGER files_custom_insert AFTER INSERT ON files
--    BEGIN
--        INSERT INTO files_custom(fid) VALUES(NEW.fid);
--    END;
--
--CREATE TRIGGER files_custom_delete DELETE ON files
--    BEGIN
--        DELETE FROM files_custom WHERE fid=OLD.fid;
--    END;
--
---- Playlistdata Custom Trigger
--CREATE TRIGGER playlistdata_custom_delete DELETE ON playlists
--    BEGIN
--        DELETE FROM playlistdata_custom WHERE plid=OLD.plid;
--    END;
--

COMMIT;
