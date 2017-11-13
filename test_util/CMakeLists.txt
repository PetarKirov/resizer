cmake_minimum_required (VERSION 3.2)
project(test_util)

file(GLOB SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES})
add_library(test_util::lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif (MSVC)
