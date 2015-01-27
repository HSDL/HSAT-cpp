#ifndef METAOPTIM_HPP
#define METAOPTIM_HPP

#include <iostream>
#include <cmath>
#include <numeric>

#include "utils.hpp"
#include "multipleteams.hpp"
#include "parameters.hpp"

using namespace std;

class Search {
public:
    Search();
    void parse_param_file(string file_name);
    void save_settings(string file_name);

    //// Variables
    Parameters p_best;       // The parameters of the simulation
    vector<string> var_name;
    vector<double> var_vals;
    vector<double> lower_lims;
    vector<double> upper_lims;
    vector<double> step_sizes;
};

class PatternSearch : public Search {
public:
    //// Functions
    PatternSearch(string file_name); // A function to construct the thing.
    void solve(int max_iter);  // A function to solve the problem.
    
    //// Variables
    int current_iteration;
    double fx_best;

private:
    // nothing yet
};

class UnivariateSearch : public Search {
public:
    //// Functions
    UnivariateSearch(string file_name); // A function to construct the thing.
    void solve(int max_iter);  // A function to solve the problem.

    //// Variables
    int current_iteration;
    double fx_best;

private:
    // nothing yet
};

#endif