cmake_minimum_required(VERSION 3.16.3)

project(Genetic_Algorithm_Example)

add_compile_options(-Wall -pedantic -std=c++17 -g)

file(GLOB SOURCE "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCE})

include_directories(include)

target_link_libraries(${PROJECT_NAME} m)
