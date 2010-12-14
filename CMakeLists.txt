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

add_executable(
    tatoeba
    src/main.cpp
    src/tatoeba.cpp
    ${controllers_files}
    simple.cpp
)

target_link_libraries(
    tatoeba
    tato
    cppcms
    booster
    sqlite3
)

add_custom_command(
    OUTPUT simple.cpp
    COMMAND cppcms_tmpl_cc 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/*/*.tmpl 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/*.tmpl
        -o simple.cpp
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/*/*.tmpl 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/*.tmpl
)
