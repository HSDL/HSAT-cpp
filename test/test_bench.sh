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
./build/bin/HSAT_BENCH ./test/example_bench.txt ./test/output_bench.txt

exit 0
