cmake_minimum_required(VERSION 3.20)
project(2_1)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/dist/${CMAKE_SYSTEM_NAME})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

find_package(Python3 3.10 REQUIRED COMPONENTS Interpreter Development)

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
    message(INFORMATION ${Python3_RUNTIME_LIBRARY_DIRS})

    file(GLOB PYTHON_DLLS ${Python3_RUNTIME_LIBRARY_DIRS}/python*.dll)

    foreach(DLL ${PYTHON_DLLS})
        # Copy assets into build directory -- used for non-emscripten builds
        add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${DLL} ${OUTPUT_DIR})
    endforeach()
endif()


add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/python/ ${OUTPUT_DIR}/python)