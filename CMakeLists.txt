cmake_minimum_required (VERSION 3.2)

project(image-resizer
    VERSION 0.0.1
    DESCRIPTION "A library for resizing bmp images"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/include/config/config.h.in"
    "${PROJECT_SOURCE_DIR}/include/config/config.h"
)

include_directories(include)
add_executable(test_cmake src/test_cmake.cpp)
