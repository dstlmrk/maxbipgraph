cmake_minimum_required(VERSION 3.6)
project(maxbipgraph)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/CGraph.cpp src/CGraph.h src/CResult.cpp src/CResult.h src/CMaxBigraph.cpp src/CMaxBigraph.h)
add_executable(maxbipgraph ${SOURCE_FILES})