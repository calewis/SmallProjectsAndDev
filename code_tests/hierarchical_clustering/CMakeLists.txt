cmake_minimum_required (VERSION 2.8.11)
project (HierarchicalClustering)

set(CMAKE_CXX_FLAGS "${CXXFLAGS} -std=c++11")
add_executable(atom_example atom_example.cpp atom.cpp)

set(srcs_files 
    atom.cpp
    clusterable.cpp
    )

add_executable(example clusterable_example.cpp ${srcs_files})
