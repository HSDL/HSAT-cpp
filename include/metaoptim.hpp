#ifndef METAOPTIM_HPP
#define METAOPTIM_HPP

#include <iostream>
#include <cmath>
#include <numeric>

#include "utils.hpp"
#include "multipleteams.hpp"
#include "parameters.hpp"

using namespace std;

class PatternSearch {
public:
    //// Functions
    PatternSearch(string file_name); // A function to construct the thing.
    void solve(int max_iter);  // A function to solve the problem.
    
    //// Variables
    Parameters p;       // The parameters of the simulation
    int current_iteration;
    vector<string> var_list;
    vector<double> var_vals;
    vector<double> step_sizes;
    double fx_current;

private:
    // nothing yet
};

#endif