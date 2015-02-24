#ifndef MAKERANDOM_HPP
#define MAKERANDOM_HPP

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// Function to return a uniform double
double uniform(double ub, double lb);

// Function to seed wrt time
void seed_time(void);

// Function to return a uniform random vector
vector<double> random_vector(int D, double ub, double lb);

// Weighted random choice function
int weighted_choice(vector<double> x);

#endif