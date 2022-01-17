cmake_minimum_required(VERSION 3.20)
project(4_4)

set(CMAKE_CXX_STANDARD 20)
set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

add_executable(4_4 main.cpp)

file(GLOB TXT_FILES ${CMAKE_SOURCE_DIR}/*.txt)

foreach(TXT_FILE ${TXT_FILES})
    # Copy assets into build directory -- used for non-emscripten builds
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${TXT_FILE} ${OUTPUT_DIR}/)
endforeach()