cmake_minimum_required (VERSION 2.8.11)
project (memory)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/test_memory.cpp src/OS32Memory.h src/OS32Memory.cpp
    src/File.cpp src/File.h src/FileSystem.cpp src/FileSystem.h)
add_executable(memory ${SOURCE_FILES})
set(SOURCE_FILES src/File.cpp src/File.h src/FileSystem.cpp src/FileSystem.h src/test_FS.cpp)
add_executable(fileSystem ${SOURCE_FILES})
