BEGIN EXCLUSIVE;

-- *******************************************************************************
-- *******************************************************************************
-- @table ipod_metadata
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
CREATE TABLE ipod_metadata (
      fid              INTEGER PRIMARY KEY NOT NULL REFERENCES files,
      offset           TEXT DEFAULT '' NOT NULL,
      caps             INTEGER DEFAULT 0 NOT NULL,
      composer         INTEGER DEFAULT 1 NOT NULL REFERENCES ipod_composers,
      uid              INTEGER DEFAULT 0 NOT NULL,
      chp_count        INTEGER DEFAULT 0 NOT NULL,
      chp_times        TEXT DEFAULT NULL,
      chp_name         TEXT DEFAULT NULL,
      podcast_date     TEXT DEFAULT NULL,
      play_count       INTEGER DEFAULT 0 NOT NULL,
      skip_count       INTEGER DEFAULT 0 NOT NULL,
      last_play        TEXT DEFAULT NULL,
      series_name      TEXT DEFAULT NULL,
      season_num       INTEGER DEFAULT 0 NOT NULL,
      vol_adjust       INTEGER DEFAULT 0 NOT NULL,
      eq_preset        TEXT DEFAULT NULL,
      book_off         INTEGER DEFAULT 0 NOT NULL,
      time_off         INTEGER DEFAULT 0 NOT NULL
);


-- *******************************************************************************
-- *******************************************************************************
--
-- iPod metadata support table
--
-- *******************************************************************************
-- *******************************************************************************
CREATE TABLE ipod_composers (
      composer_id      INTEGER PRIMARY KEY AUTOINCREMENT,
      composer         TEXT
);
CREATE INDEX ipod_composers_index_composer on ipod_composers(composer);
-- Unknown is always 1
INSERT INTO ipod_composers(composer_id, composer)
   VALUES(1, NULL);


-- *****************
-- Required TRIGGERS
-- *****************
--
---- Metadata custom triggers --
CREATE TRIGGER ipod_metadata_delete AFTER DELETE on files
   BEGIN
      DELETE FROM ipod_metadata WHERE fid=OLD.fid;
   END;

COMMIT;
