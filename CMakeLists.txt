cmake_minimum_required(VERSION 3.6)
project(maxbipgraph)

SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O3")

set(SOURCE_FILES main.cpp src/CGraph.cpp src/CGraph.h)
add_executable(maxbipgraph ${SOURCE_FILES})