cmake_minimum_required(VERSION 3.20)
project(2_1)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/dist/${CMAKE_SYSTEM_NAME})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${Python3_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${Python3_LIBRARIES}
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Copy assets into build directory -- used for non-emscripten builds
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${Python3_RUNTIME_LIBRARY_DIRS}/python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}.dll ${OUTPUT_DIR})
endif()

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/python/ ${OUTPUT_DIR}/python)