cmake_minimum_required (VERSION 3.2)

project(image-resizer)

set(CMAKE_PROJECT_DESCRIPTION
    "A C++ library and a node module for resizing .bmp image files"
)

if (MSVC)
    add_compile_options(/W4)
else (MSVC)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif (MSVC)

option(USE_CPP11 "Use C++ 11, instead of C++98" ON)

if (USE_CPP11)
    set(CMAKE_CXX_STANDARD 11)
else (USE_CPP11)
    set(CMAKE_CXX_STANDARD 98)
endif (USE_CPP11)

add_subdirectory(test_util)
add_subdirectory(image)
add_subdirectory(tests/test1)
add_subdirectory(tests/test_slice)
