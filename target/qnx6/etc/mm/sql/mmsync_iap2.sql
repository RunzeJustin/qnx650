BEGIN EXCLUSIVE;

-- *******************************************************************************
-- *******************************************************************************
-- @table iap2_last_revision
--
-- The ipod_metadata contains metadata specific to ipod tracks.
--
-- @field rev              The last successful revision.
-- *******************************************************************************
-- *******************************************************************************
CREATE TABLE iap2_last_revision (
      rev              INTEGER PRIMARY KEY NOT NULL
);

-- *******************************************************************************
-- *******************************************************************************
-- @table iap2_metadata
--
-- The ipod_metadata contains metadata specific to ipod tracks.
--
-- @field fid              The file ID (fid) for the media track.
-- @field offset           iPod offset.
-- @field caps             iPod capabilities.
-- @field composer         iPod composer.
-- @field uid              iPod track unique ID (cast to a uint64_t after reading
--                         this value from the database).
-- @field chp_count        iPod chapter count.
-- @field chp_times        iPod chapter times.
-- @field chp_name         iPod chapter name.
-- @field podcast_date     iPod podcast date.
-- @field play_count       iPod play count.
-- @field skip_count       iPod skip count.
-- @field last_play        iPod last played time.
-- @field series_name      iPod series name.
-- @field season_num       iPod season number.
-- @field vol_adjust       iPod volume adjust.
-- @field eq_preset        iPod equalizer preset.
-- @field book_off         iPod book offset.
-- @field time_off         iPod time offset.
-- *******************************************************************************
-- *******************************************************************************
--CREATE TABLE iap2_metadata (
--      fid              INTEGER PRIMARY KEY NOT NULL REFERENCES files,
--      uid              TEXT DEFAULT NULL,
--      type             TEXT DEFAULT NULL,
--      rating           TEXT DEFAULT NULL,
--      composer         INTEGER DEFAULT 1 NOT NULL REFERENCES iap2_composers,
--      album_uid        INTEGER DEFAULT 1 NOT NULL REFERENCES iap2_album_uids,
--      artist_uid       INTEGER DEFAULT 1 NOT NULL REFERENCES iap2_artist_uids,
--      genre_uid        INTEGER DEFAULT 1 NOT NULL REFERENCES iap2_genre_uids,
--      composer_uid     INTEGER DEFAULT 1 NOT NULL REFERENCES iap2_composer_uids
--);


-- *******************************************************************************
-- *******************************************************************************
--
-- iPod metadata support table
--
-- *******************************************************************************
-- *******************************************************************************
--CREATE TABLE iap2_composers (
--      composer_id      INTEGER PRIMARY KEY AUTOINCREMENT,
--      composer         TEXT
--);
--CREATE INDEX iap2_composers_index_composer ON iap2_composers(composer);
-- Unknown is always 1
--INSERT INTO iap2_composers(composer_id, composer)
--   VALUES(1, NULL);

--CREATE TABLE iap2_album_uids (
--      id               INTEGER PRIMARY KEY AUTOINCREMENT,
--      album_uid        TEXT
--);
--CREATE INDEX iap2_album_uids_index_album_uid ON iap2_album_uids(album_uid);
-- Unknown is always 1
--INSERT INTO iap2_album_uids(id, album_uid)
--   VALUES(1, NULL);

--CREATE TABLE iap2_artist_uids (
--      id               INTEGER PRIMARY KEY AUTOINCREMENT,
--      artist_uid       TEXT
--);
--CREATE INDEX iap2_artist_uids_index_artist_uid ON iap2_artist_uids(artist_uid);
-- Unknown is always 1
--INSERT INTO iap2_artist_uids(id, artist_uid)
--   VALUES(1, NULL);

--CREATE TABLE iap2_genre_uids (
--      id               INTEGER PRIMARY KEY AUTOINCREMENT,
--      genre_uid        TEXT
--);
--CREATE INDEX iap2_genre_uids_index_genre_uid ON iap2_genre_uids(genre_uid);
-- Unknown is always 1
--INSERT INTO iap2_genre_uids(id, genre_uid)
--   VALUES(1, NULL);

--CREATE TABLE iap2_composer_uids (
--      id               INTEGER PRIMARY KEY AUTOINCREMENT,
--      composer_uid     TEXT
--);
--CREATE INDEX iap2_composer_uids_index_composer_uid ON iap2_composer_uids(composer_uid);
-- Unknown is always 1
--INSERT INTO iap2_composer_uids(id, composer_uid)
--   VALUES(1, NULL);

-- *****************
-- Required TRIGGERS
-- *****************
--
---- Metadata custom triggers --
--CREATE TRIGGER iap2_metadata_delete AFTER DELETE on files
--   BEGIN
--      DELETE FROM iap2_metadata WHERE fid=OLD.fid;
--   END;

-- **********************
-- Optional Tables (IAP2)
-- **********************
--
-- *******************************************************************************
-- *******************************************************************************
-- @table iap2_revision_history
--
-- This table tracks the complete revision history of the iPod.  It is used more
-- for debugging although technically it can be used to continue a sync from any
-- point on the iPod although this may leave the database in an incosistent state.
--
-- @field rev              The revision ID from the iPod.
-- @field uid              iPod UID of the last known entry before the revision.
-- @field type             The type associated with the stored UID.
-- *******************************************************************************
-- *******************************************************************************
--CREATE TABLE iap2_revision_history (
--      rev              INTEGER NOT NULL,
--      uid              TEXT NOT NULL,
--      type             INTEGER,
--      primary key(rev, type)
--);

-- ***********************
-- Optional Indexes (IAP2)
-- ***********************
--
-- Indexing the files.filename field will speed up deletions and the playlist entry to filename mapping
-- done during the playlist sync at the expense of DB size (IAP2).
-- CREATE INDEX files_index_filename ON files(filename);
--
-- Indexing the playlist_entries.unresolved_entry_text field will drastically speed up playlist entry to
-- filename mapping done during the playlist sync at the expense of DB size (IAP2).
-- CREATE INDEX playlist_entries_index_unresolved_entry_text ON playlist_entries(unresolved_entry_text);

COMMIT;


