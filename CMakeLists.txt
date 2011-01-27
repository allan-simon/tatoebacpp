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
    generics_files
    src/generics/*
)




add_executable(
    tatoeba
    src/main.cpp
    src/tatoeba.cpp
    ${controllers_files}
    ${models_files}
    ${generics_files}
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
    COMMAND ./../tools/cppcms_tmpl_cc 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/*/*.tmpl 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/*.tmpl
        -o simple.cpp
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/*/*.tmpl 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/*.tmpl
)
