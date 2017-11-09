cmake_minimum_required (VERSION 3.2)
project(image
    VERSION 0.0.1
)

configure_file(
    "${PROJECT_SOURCE_DIR}/include/image/config/config.h.in"
    "${PROJECT_BINARY_DIR}/include/image/config/config.h"
)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES})
add_library(image::lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
)
