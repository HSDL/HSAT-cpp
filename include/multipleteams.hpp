#ifndef MULTIPLETEAMS_HPP
#define MULTIPLETEAMS_HPP

#include <iostream>
#include <cmath>
#include <numeric>

#include "utils/stats.hpp"
#include "agent.hpp"
#include "team.hpp"
#include "parameters.hpp"

class MultipleTeams {
public:
    //// Functions
    MultipleTeams(Parameters x); // A function to construct the thing from an object
    MultipleTeams(string file_name); // A function to construct the thing from file
    double solve(void);  // A function to solve the problem.

    //// Variables
    Parameters p;       // The parameters of the simulation
    vector<double> cdf; // Stores the best value found in every run
    vector<vector<double>> best_solution; // Stores the string of best values from every run.

private:
    // nothing yet
};

#endif