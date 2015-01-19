#ifndef METAOPTIM_HPP
#define METAOPTIM_HPP

#include <iostream>
#include <cmath>
#include <numeric>

#include "utils.hpp"
#include "multipleteams.hpp"
#include "parameters.hpp"

class PatternSearch {
public:
    //// Functions
    PatternSearch(void); // A function to construct the thing.
    Parameters solve(void);  // A function to solve the problem.

    //// Variables
    Parameters p;       // The parameters of the simulation

private:
    // nothing yet
};

class SteepestDescent {
public:
    //// Functions
    SteepestDescent(void); // A function to construct the thing.
    Parameters solve(void);  // A function to solve the problem.

    //// Variables
    Parameters p;       // The parameters of the simulation

private:
    // nothing yet
};

#endif