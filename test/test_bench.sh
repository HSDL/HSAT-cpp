#!/bin/bash

# Test the benchmarking functionality
cd ..
./build/bin/hsat --bench --input ./test/example_bench.txt --output ./test/output_bench.txt --verbose

exit 0
