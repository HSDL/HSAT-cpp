#ifndef UNIVARIATE_HPP
#define UNIVARIATE_HPP

#include "../agent_team/multipleteams.hpp"
#include "search.hpp"

using namespace std;

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