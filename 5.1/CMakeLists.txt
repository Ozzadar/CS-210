cmake_minimum_required(VERSION 3.20)
project(5_1)

set(CMAKE_CXX_STANDARD 20)
set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

add_subdirectory(third-party/fmt)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        fmt
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        src/
        include/
        fmt
)
