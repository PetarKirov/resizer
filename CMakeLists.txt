cmake_minimum_required (VERSION 3.2)

project(resizer)

set(CMAKE_PROJECT_DESCRIPTION
    "A C++ library and a node module for resizing .bmp image files"
)

option(USE_CPP11 "Use C++ 11, instead of C++98" ON)

if (USE_CPP11)
    set(CMAKE_CXX_STANDARD 11)
else (USE_CPP11)
    set(CMAKE_CXX_STANDARD 98)
endif (USE_CPP11)

add_subdirectory(test_util)
add_subdirectory(image)
add_subdirectory(tests)

if (CMAKE_JS_VERSION)
    add_library(${PROJECT_NAME} SHARED resizer-node/node_entry_point.cpp)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})
    message (STATUS "XXXX: " ${CMAKE_JS_INC})
    set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
    target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
endif ()
