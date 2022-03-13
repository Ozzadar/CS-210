cmake_minimum_required(VERSION 3.20)
project(7_1)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/dist/${CMAKE_SYSTEM_NAME})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include/
        ${Python3_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${Python3_LIBRARIES}
)

# If we're on windows, we need to copy the dlls into our runtime folder
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(INFORMATION ${Python3_RUNTIME_LIBRARY_DIRS})

    file(GLOB PYTHON_DLLS ${Python3_RUNTIME_LIBRARY_DIRS}/python*.dll)

    foreach(DLL ${PYTHON_DLLS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${DLL} ${OUTPUT_DIR})
    endforeach()
endif()

# This command copies all our python scripts to the running directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/python/ ${OUTPUT_DIR}/python)

# This command copies our input data folder to the running directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data/ ${OUTPUT_DIR}/data)