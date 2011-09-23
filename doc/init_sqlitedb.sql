-- script to create tables used by tatoebacpp
CREATE TABLE users (
"id"          integer primary key not null , 
"username"    text    not null unique,             -- his nickname 
"email"       text    not null unique,             -- his email address
"image"       text    not null default "unknown" , -- his personnal image 
"password"    text    not null,                    -- his password hashed
"depth"       integer not null default 2,          -- the default depth of translation
"since"       integer not null,                    -- his registering date
"homepage"    text    default "",                  -- his personnal webpage/website
"description" text    default ""                   -- his self-written description

);
CREATE INDEX users_username_idx ON users (username);
--
--
CREATE TABLE users_spoken_langs (
    "user_id"       integer not null, -- id of the user 
    "lang"          text    not null, -- ... language he speaks
    "proeficiency"  integer not null, -- ... with which proeficiency
    "is_native"     boolean not null  -- ... if he's a native of that language
);
CREATE INDEX users_spoken_langs_user_id_idx
    ON users_spoken_langs (user_id);
-- constraint to be sure we don't add two time a couple (user,lang)
CREATE UNIQUE INDEX users_spoken_langs_user_id_lang_idx
    ON users_spoken_langs (user_id , lang);
--
--
CREATE TABLE sentence_users (
    "sentence_id"  integer primary key not null, -- id of the sentence
    "user_id"      integer,                      -- id of the owner (can be null if orphan)
    "lang_id"      integer                       -- id of the language of this sentence (can be null if unknown)
);

CREATE INDEX sentences_users_user_id_idx
    ON sentence_users (user_id);

CREATE INDEX sentences_users_user_id_lang_id_idx
    ON sentence_users (user_id, lang_id);

--
--

-- Table that will contain the info about a new tag that is requested by
-- a user to be added in the list of supported tags
-- @since 15 September 2011
CREATE TABLE requested_tags (
    "id"             integer primary key not null, 
    "internal_name"  text not null,                -- internal representation of the name, url friendly, for collation etc.
    "name"           text not null,                -- name of the tag in human readable format
    "description"    text not null,                -- text describing the purpose of this tag
    "user_id"        integer not null,             -- id of the user who added it
    "created"        integer not null,             -- date when it has been added
    "nbrOfSentences" integer not null default 0    -- number of sentences tagged with this tag
);


CREATE UNIQUE INDEX requested_tags_internal_name_idx
    ON requested_tags (internal_name);

-- Table that will contain the info about tags supported by the system
-- @since 15 September 2011
CREATE TABLE tags (
    "id"             integer primary key not null, 
    "internal_name"  text not null,                -- internal representation of the name, url friendly, for collation etc.
    "name"           text not null,                -- name of the tag in human readable format
    "description"    text not null,                -- text describing the purpose of this tag
    "user_id"        integer not null,             -- id of the user who added it
    "created"        integer not null,             -- date when it has been added
    "nbrOfSentences" integer not null default 0    -- number of sentences tagged with this tag
);

CREATE UNIQUE INDEX tags_internal_name_idx
    ON tags (internal_name);

-- Table that will contain info about which sentence has which tags, when
-- the tag has been added on this sentence and by who
--
-- @since 20 September 2011
    
CREATE TABLE tags_sentences (
    "tag_id"        integer not null,           -- id of the tag that has been added
    "sentence_id"   integer not null,           -- on which sentence (its id)
    "lang_id"       integer not null,           -- id of the sentence language
    "user_id"       integer not null,           -- id of the user who has added this tag on this sentence
    "added_time"    integer not null default 0  -- timestamp when the tag has been added
);

CREATE INDEX tags_sentences_tag_id_idx
    ON tags_sentences(tag_id);

CREATE INDEX tags_sentences_sentence_id_idx
    ON tags_sentences(sentence_id);

CREATE INDEX tags_sentences_added_time_idx
    ON tags_sentences(added_time);

CREATE UNIQUE INDEX tags_sentences_tag_id_sentence_id_idx
    ON tags_sentences(tag_id, sentence_id);
