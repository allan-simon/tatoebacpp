-- script to create tables used by tatoebacpp

CREATE TABLE users (
"id" integer primary key not null ,
"username" text not null unique,
"email" text not null unique,
"password" blob not null
);
