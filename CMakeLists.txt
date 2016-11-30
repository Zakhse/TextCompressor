cmake_minimum_required(VERSION 3.5)
project(TextCompressor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BitWriter.cpp compressor.cpp huffman.cpp for_debug.cpp BitReader.cpp shannon_fano.cpp)
add_executable(TextCompressor ${SOURCE_FILES})