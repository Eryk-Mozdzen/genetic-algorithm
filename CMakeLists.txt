cmake_minimum_required(VERSION 3.16.3)

project(genetic-algorithm)

add_executable(${PROJECT_NAME}
    "src/main.cpp"
    "src/String.cpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "include"
)

target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall
    -Wextra
    -Wpedantic
)
