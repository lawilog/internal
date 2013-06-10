cmake_minimum_required(VERSION 2.6)
include_directories(/usr/include/openbabel-2.0/)

add_definitions(-Wall -std=c++0x -O2)

add_executable(test test.cpp)
target_link_libraries(test openbabel)

add_executable(pdb2tikz pdb2tikz.cpp)
target_link_libraries(pdb2tikz openbabel)
