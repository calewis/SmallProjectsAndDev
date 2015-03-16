# Project which will generate linear alkane chains.  This project will 
# likely be expanded in the future.

cmake_minimum_required(VERSION 2.8.11)
project(MoleculeGenerater)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/include")

add_executable(alkane_chains alkane_chains.cpp)
target_link_libraries(alkane_chains -lopenbabel)
