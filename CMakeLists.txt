cmake_minimum_required(VERSION 2.8.4)
project(HSAT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

set(SOURCE_FILES_SINGLE
    src/main_bench.cpp
    include/utils.hpp
    include/agent.hpp
    include/parameters.hpp
    include/team.hpp
    include/multipleteams.hpp
    src/utils.cpp
    src/agent.cpp
    src/parameters.cpp
    src/team.cpp
    src/multipleteams.cpp)

add_executable(HSAT ${SOURCE_FILES_SINGLE})