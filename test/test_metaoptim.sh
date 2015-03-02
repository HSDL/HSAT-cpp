#!/bin/bash

# Test the metaoptimization functionality
cd ..
./build/bin/hsat --univariate 5 --input ./test/example_bench.txt --output ./test/output_bench.txt --verbose

exit 0