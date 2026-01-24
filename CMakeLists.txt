cmake_minimum_required(VERSION 3.16)

project(tic VERSION 0.1 LANGUAGES C RC)

set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})

set(INCLUDE_FILES
    grf.h
    field.h
    atlas.h
)

set(SRC_FILES
    grf.c
    main.c
    field.c
    atlas.c
)

list(TRANSFORM INCLUDE_FILES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/include/)
list(TRANSFORM SRC_FILES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/src/)

add_executable(minefield ${INCLUDE_FILES} ${SRC_FILES} res/resource.rc)
target_include_directories(minefield PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_options(minefield PRIVATE -SUBSYSTEM:WINDOWS)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_property(TARGET minefield PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif()