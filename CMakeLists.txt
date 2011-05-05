cmake_minimum_required(VERSION 2.6)

project(tatoebacpp)
include_directories(
    src
)

file(
    GLOB
    controllers_files
    src/controllers/*
)

file(
    GLOB
    models_files
    src/models/*
)

file(
    GLOB
    results_files
    src/results/*
)

file(
    GLOB
    contents_files
    src/contents/*
)


file(
    GLOB
    generics_files
    src/generics/*
)




add_executable(
    tatoeba
    src/tatoeba.cpp
    src/main.cpp
    ${controllers_files}
    ${models_files}
    ${generics_files}
    ${results_files}
    ${contents_files}
    simple.cpp
)

target_link_libraries(
    tatoeba
    tato
    cppcms
    cppdb
    booster
    sqlite3
)

add_custom_command(
    OUTPUT simple.cpp
    COMMAND ../tools/cppcms_tmpl_cc 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/*/*.tmpl 
        -o simple.cpp
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/*/*.tmpl 
)
