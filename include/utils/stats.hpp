#ifndef STATS_HPP
#define STATS_HPP

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

// Function to return maximum value of vector
double vector_max(vector<double> v);

// Function to return minimum value of vector
double vector_min(vector<double> v);

// Compute mean of a vector
double mean(vector<double> x);

// Compute mean of a deque
double stdev(deque<double> x);

// Compute standard deviation of a list
double stdev(deque<double> x);

// Compute the x value for the optimium of a linear regression
vector<double> quad_max(vector<double> x, vector<double> y);

#endif