# HSAT [![Build Status](https://travis-ci.org/cmccomb/HSAT.svg?branch=master)](https://travis-ci.org/cmccomb/HSAT)

Building using Cmake will produce two binary files:
  1. **HSAT_BENCH**: Will benchmark the algorithm for given inputs. Syntax is:

  ```
  HSAT_BENCH input_file.txt output_file.txt
  ```
  
  2. **HSAT_OPTIM**: Will optimize the parameters of the algorithms for given inputs. Syntax is:

  ```
  HSAT_BENCH max_iter input_file.txt output_file.txt
  ```
