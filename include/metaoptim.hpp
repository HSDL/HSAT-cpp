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
    PatternSearch(void); // A function to construct the thing.
    void set_from_file(string file_name);
    void solve(int max_iter);  // A function to solve the problem.


    //// Variables
    Parameters p;       // The parameters of the simulation
    int current_iteration;
    vector<string> variables;
    vector<double> step_sizes;
    double fx_current;

private:
    // nothing yet
};

#endif