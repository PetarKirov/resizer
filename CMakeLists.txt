cmake_minimum_required (VERSION 3.2)

project(image-resizer
    VERSION 0.0.1
)

set(PROJECT_DESCRIPTION
    "A C++ library and a node module for resizing .bmp image files"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/include/config/config.h.in"
    "${PROJECT_SOURCE_DIR}/include/config/config.h"
)

option(USE_CPP11
    "Use C++ 11, insteadof C++03" ON)

if (USE_CPP11)
    set(CMAKE_CXX_STANDARD 11)
else (USE_CPP11)
    set(CMAKE_CXX_STANDARD 98)
endif (USE_CPP11)

include_directories(include)
add_executable(test_cmake src/test_cmake.cpp)
