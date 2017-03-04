cmake_minimum_required(VERSION 3.6)
project(maxbipgraph)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CGraph.cpp CGraph.h)
add_executable(maxbipgraph ${SOURCE_FILES})