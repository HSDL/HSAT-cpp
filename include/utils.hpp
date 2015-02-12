#ifndef UTILS_HPP
#define UTILS_HPP

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

// Function to return a uniform double
double uniform(double ub, double lb);

// Function to seed wrt time
void seed_time(void);

// Function to return a uniform random vector
vector<double> random_vector(int D, double ub, double lb);

// Functions to print variables
void print(int x);
void print(double x);
void print(vector<double>);
void print(vector<double>::size_type x);

// Function to return maximum value of vector
double vector_max(vector<double> v);

// Function to return minimum value of vector
double vector_min(vector<double> v);

// Write to file
void save_to_file(string file_path, vector<double>);
void save_to_file(string file_path, vector<vector<double>>);

// Weighted random choice function
int weighted_choice(vector<double> x);

// Compute mean of a vector
double mean(vector<double> x);

// Compute mean of a deque
double stdev(deque<double> x);

// Compute standard deviation of a list
double stdev(deque<double> x);

// Compute the x value for the optimium of a linear regression
vector<double> quad_max(vector<double> x, vector<double> y);

// Computes the pearson-r value between two vectors
vector<double> pearsonr(vector<double> x, vector<double> y);

#endif