cmake_minimum_required(VERSION 2.8.4)
project(HSAT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/Users/IDIG/Dropbox/Research_CMU_WaveTeams/HSAT/bin")

set(SOURCE_FILES
    main.cpp
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

add_executable(HSAT ${SOURCE_FILES})