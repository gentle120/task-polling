cmake_minimum_required(VERSION 3.22)

project(demo)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ./task.cpp
)   

target_include_directories(${PROJECT_NAME}  PRIVATE
    ./
)