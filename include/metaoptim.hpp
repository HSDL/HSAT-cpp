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
    Parameters p_best;       // The parameters of the simulation
    int current_iteration;
    vector<string> var_name;
    vector<double> var_vals;
    vector<double> lower_lims;
    vector<double> upper_lims;
    vector<double> step_sizes;
    double fx_best;

private:
    // nothing yet
};

class UnivariateSearch {
public:
    //// Functions
    UnivariateSearch(string file_name); // A function to construct the thing.
    void solve(int max_iter);  // A function to solve the problem.

    //// Variables
    Parameters p_best;       // The parameters of the simulation
    int current_iteration;
    vector<string> var_name;
    vector<double> var_vals;
    vector<double> lower_lims;
    vector<double> upper_lims;
    vector<double> step_sizes;
    double fx_best;

private:
    // nothing yet
};

#endif