#include "../../include/utils/makerandom.hpp"

//// This returns a uniform double between upper and lower bounds
double uniform(double ub, double lb){
    return lb + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(ub-lb)));
}

//// Seeds rand with the current time
void seed_time(void){
    srand(static_cast <unsigned> (time(0)));
}

//// Creates a random vector
vector<double> random_vector(int D, double ub, double lb){
    // Initialize a vector
    vector<double> x(D, 0.0);

    // Create the elements in that vector
    for(int i=0; i<D; i++){
        x[i] = uniform(ub, lb);
    }

    // Return the vector
    return x;
}


// Weighted random choice function
int weighted_choice(vector<double> x){
    // Get the sum of the vector
    double sum = 0;
    for(vector<double>::iterator j=x.begin(); j!=x.end();++j)
        sum += *j;

    // Get a random value somewhere within the vector CDF
    sum *= uniform(0.0, 1.0);

    // Step through the vector (i.e. spin the wheel)
    for(int i=0; i < x.size(); i++) {
        sum -= x[i];
        if (sum <= 0) {
            return i;
        }
    }

    // If the above didn't return anything, return a equal-weighted random number.
    return rand() % (int)x.size();
}