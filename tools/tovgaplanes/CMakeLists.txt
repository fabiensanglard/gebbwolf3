cmake_minimum_required(VERSION 3.6)
project(tovgaplanes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ImageTGA.cpp ImageTGA.h ByteStream.cpp ByteStream.h)
add_executable(tovgaplanes ${SOURCE_FILES})