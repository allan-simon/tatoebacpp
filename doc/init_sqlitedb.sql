-- script to create tables used by tatoebacpp
CREATE TABLE users (
"id"          integer primary key not null , 
"username"    text    not null unique,             -- his nickname 
"email"       text    not null unique,             -- his email address
"image"       text    not null default "unknown" , -- his personnal image 
"password"    text    not null,                    -- his password hashed
"since"       integer not null,                    -- his registering date
"homepage"    text    default "",                  -- his personnal webpage/website
"description" text    default ""                   -- his self-written description

);
CREATE INDEX users_username_idx ON users (username);
--
CREATE TABLE users_spoken_langs (
    "user_id"       integer not null, -- id of the user 
    "lang"          text    not null, -- ... language he speaks
    "proeficiency"  integer not null, -- ... with which proeficiency
    "is_native"      boolean not null  -- ... if he's a native of that language
);
CREATE INDEX users_spoken_langs_user_id_idx
    ON users_spoken_langs (user_id);
-- constraint to be sure we don't add two time a couple (user,lang)
CREATE UNIQUE INDEX users_spoken_langs_user_id_lang_idx
    ON users_spoken_langs (user_id , lang);
--

