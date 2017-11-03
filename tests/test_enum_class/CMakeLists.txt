cmake_minimum_required (VERSION 3.2)
project (test_enum_class)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
    test_util::lib
    image::lib
)
