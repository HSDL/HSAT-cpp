cmake_minimum_required(VERSION 2.8.4)
project(HSAT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

set(SOURCE_FILES_BENCH
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


set(SOURCE_FILES_OPTIM
    src/main_optimize.cpp
    include/utils.hpp
    include/agent.hpp
    include/parameters.hpp
    include/team.hpp
    include/multipleteams.hpp
    include/metaoptim.hpp
    src/utils.cpp
    src/agent.cpp
    src/parameters.cpp
    src/team.cpp
    src/multipleteams.cpp
    src/metaoptim.cpp)

add_executable(HSAT_BENCH ${SOURCE_FILES_BENCH})
add_executable(HSAT_OPTIM ${SOURCE_FILES_OPTIM})