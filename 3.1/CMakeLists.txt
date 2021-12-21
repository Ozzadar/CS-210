cmake_minimum_required(VERSION 3.20)
project(3_1)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE CPP_SOURCES src/*.cpp)
add_executable(3_1 ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include/
)