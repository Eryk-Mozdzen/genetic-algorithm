cmake_minimum_required(VERSION 3.16)

project(genetic-algorithm-c)

add_executable(${PROJECT_NAME}
    "src/main.c"
    "src/member.c"
    "src/genetic.c"
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
