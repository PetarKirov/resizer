cmake_minimum_required (VERSION 3.2)
project(image
    VERSION 0.0.1
)

configure_file(
    "${PROJECT_SOURCE_DIR}/include/config/config.h.in"
    "${PROJECT_SOURCE_DIR}/include/config/config.h"
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(image::lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include
)
