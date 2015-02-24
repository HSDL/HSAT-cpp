#!/bin/bash

# Clean the build directory
cd ..
rm -rf build

# Make a new one
mkdir build
cd build

# Build the project
cmake ..
make

# Test the benchmarking function
cd ..
./build/bin/HSAT_OPTIM 3 ./test/example_metaoptim.txt ./test/output_metaoptim.txt