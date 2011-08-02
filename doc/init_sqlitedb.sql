-- script to create tables used by tatoebacpp

CREATE TABLE users (
"id" integer primary key not null , 
"username" text not null unique, -- his nickname 
"email" text not null unique,    -- his email address
"password" blob not null,        -- his password in binary md5 
"since" integer not null,        -- his registering date
"description" text default ""    -- his self-written description

);
