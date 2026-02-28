cmake_minimum_required(VERSION 4.3.0)

project(
    simdetect
    VERSION 0.0.1
    DESCRIPTION "EVM disassembler and analysis runner"
    LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 23)
add_executable(SimDetect)

target_sources(SimDetect
    PRIVATE
       ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)