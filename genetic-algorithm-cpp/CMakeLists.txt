cmake_minimum_required(VERSION 3.16)

project(genetic-algorithm-cpp)

add_executable(${PROJECT_NAME}
    "src/main.cpp"
    "src/Member.cpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "include"
)

target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall
    -Wextra
    -Wpedantic
    -O3
)
