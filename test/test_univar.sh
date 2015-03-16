#!/bin/bash

# Test the metaoptimization functionality
../build/bin/hsat --univar 5 --input example_bench.txt --output output_bench.txt --verbose --parallel 2

exit 0