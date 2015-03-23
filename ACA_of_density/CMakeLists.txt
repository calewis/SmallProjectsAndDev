cmake_minimum_required(VERSION 2.8.11)

project(ACA_of_density)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/local/include/eigen3")

add_executable(density_decomp main.cpp)
