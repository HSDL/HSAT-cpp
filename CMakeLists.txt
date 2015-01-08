cmake_minimum_required(VERSION 2.8.4)
project(CIMSA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp utils.hpp utils.cpp agent.cpp agent.hpp parameters.hpp parameters.cpp team.hpp team.cpp multipleteams.cpp multipleteams.hpp)
add_executable(CIMSA ${SOURCE_FILES})