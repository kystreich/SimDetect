cmake_minimum_required(VERSION 4.3.0)
set(CMAKE_CXX_COMPILER "C:\\msys64\\ucrt64\\bin\\g++.exe")

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
lib/common/constants.h
lib/encoding/cbor.h
lib/encoding/cbor.cpp
lib/evm/opcode.h
lib/evm/opcode.cpp
lib/evm/disassembler.h
lib/evm/disassembler.cpp
lib/evm/cfg/block.h
lib/evm/cfg/block.cpp
lib/evm/cfg/cfg.h
lib/evm/cfg/cfg.cpp
lib/util/hex.h
lib/util/hex.cpp
)

add_executable(SimDetect ${SOURCES})

target_include_directories(SimDetect PRIVATE
    ${CMAKE_SOURCE_DIR}
)