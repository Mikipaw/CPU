cmake_minimum_required(VERSION 3.16)
project(Proc)

set(CMAKE_CXX_STANDARD 20)


add_executable(Proc main.cpp Assembler.cpp CPU.cpp)
target_include_directories(Proc PUBLIC C:\\Programming\\projects\\libs)
