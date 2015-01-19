cmake_minimum_required(VERSION 2.8.4)
project(HSAT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/Users/IDIG/Dropbox/Research_CMU_WaveTeams/HSAT/bin")

set(SOURCE_FILES
    main.cpp
    include/utils.hpp
    src/utils.cpp
    src/agent.cpp
    include/agent.hpp
    include/parameters.hpp
    src/parameters.cpp
    include/team.hpp
    src/team.cpp
    src/multipleteams.cpp
    include/multipleteams.hpp)

add_executable(HSAT ${SOURCE_FILES})