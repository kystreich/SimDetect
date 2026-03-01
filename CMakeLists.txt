cmake_minimum_required(VERSION 4.3.0)

project(
    SimDetect
    VERSION 0.0.1
    DESCRIPTION "EVM disassembler and analysis runner"
    LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED on)
set (CMAKE_CXX_EXTENSIONS off)

set (SOURCES
src/main.cpp
lib/logger/logger.h
lib/logger/logger.cpp
)

add_executable(SimDetect ${SOURCES})

target_include_directories(SimDetect PRIVATE
    ${CMAKE_SOURCE_DIR}
)