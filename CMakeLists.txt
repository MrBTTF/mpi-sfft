cmake_minimum_required(VERSION 3.6)
project(mpi-fft)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fopenmp")
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp AudioProcessing.h AudioProcessing.cpp)
add_executable(mpi-fft ${SOURCE_FILES})

