#include "../../include/utils/objective.hpp"

#define PI 3.141592653589793

//// Define the Griewank function
long double griewank(vector<long double> x){
    // Initialize a couple variable for sums
    long double fx1 = 0;
    long double fx2 = 1;

    // Step through every dimensions and do a thing
    for(int i=0; i < x.size(); i++){
        fx1 += x[i]*x[i];
        fx2 *= cos(x[i]/sqrt(static_cast <long double> (i+1)));
    }

    // Return a sum of sums
    return 1.0 + fx1/4000.0 - fx2;
}

//// Define the Ackley function
long double ackley(vector<long double> x){
    // Initialize a couple variable for sums
    long double fx1 = 0;
    long double fx2 = 0;
    int D = static_cast <int> (x.size());

    // Step through every dimensions and do a thing
    for(int i=0; i < D; i++){
        fx1 += x[i]*x[i];
        fx2 += cos(2*PI*x[i]);
    }

    // Return a sum of sums
    return -20.0*exp(-0.2*sqrt(fx1/D)) - exp(fx2/D) + 20.0 + exp(1.0);
}

//// Define the Rastigrin function
long double rastigrin(vector<long double> x){
    // Initialize a couple variable for sums
    long double fx = 0;

    // Step through every dimensions and do a thing
    // The funky coefficients scale the function so it falls on a [-10 10] range, instead of [-5.12, 5.12] as usual.
    for(int i=0; i < x.size(); i++){
        fx += x[i]*x[i]*0.262144 - 10*cos(2*PI*x[i]*0.512) + 10.00;
    }

    // Return a sum of sums
    return fx;
}