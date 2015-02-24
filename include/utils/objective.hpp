#ifndef OBJECTIVE_HPP
#define OBJECTIVE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <numeric>
#include <cfloat>
#include <deque>

using namespace std;

// Define the Griewank function
double griewank(vector<double> x);

// Define the Griewank function
double ackley(vector<double> x);

// Define the Griewank function
double rastigrin(vector<double> x);

#endif