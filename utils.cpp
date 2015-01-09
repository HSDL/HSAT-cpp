#include "utils.hpp"

//// Define the Griewank function
double griewank(vector<double> x){
    // Initialize a couple variable for sums
    double fx1 = 0;
    double fx2 = 1;

    // Step through every dimensions and do a thing
    for(int i=0; i < x.size(); i++){
        fx1 += x[i]*x[i];
        fx2 *= cos(x[i]/sqrt(static_cast <double> (i+1)));
    }

    // Return a sum of sums
    return 1.0 + fx1/4000.0 - fx2;
}

//// Define the Ackley function
double ackley(vector<double> x){
    return griewank(x);
}

//// Define the Rastigrin function
double rastigrin(vector<double> x){
    return griewank(x);
}

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

//// Function to print an int
void print(int x){
    cout<<x<<endl;
}

//// Function to print a double
void print(double x){
    cout<<x<<endl;
}

//// Function to print the size of a vector
void print(vector<double>::size_type x){
    cout<<x<<endl;
}

//// Function to print a vector. Black magic.
void print(vector<double> x){
    int end = static_cast <int> (x.size()-1);
    cout<<scientific<<"[ ";
    for(int i=0; i<x.size(); i++){
        if(i!=end) {
            cout << x[i] << ", ";
            if ((i + 1) % 10 == 0) {
                cout << endl << "  ";
            }
        } else {
            cout << x[i] << " ]" << endl;
        }
    }
}

//// Return the largest element in a vector.
double vector_max(vector<double> v){
    double max = -DBL_MAX;
    for(vector<double>::iterator it = v.begin(); it != v.end(); ++it) {
        if(*it > max){
            max = *it;
        }
    }
    return max;
}

//// Returns the smallest element in a vector.
double vector_min(vector<double> v){
    double min = DBL_MAX;
    for(vector<double>::iterator it = v.begin(); it != v.end(); ++it) {
        if(*it < min){
            min = *it;
        }
    }
    return min;
}

//// Save a vector to a file
void save_to_file(string file_path, vector<double> x){
    // Open a file stream
    ofstream myfile;

    // Open a file on that file stream
    myfile.open(file_path);

    // Set scientific notation. Mostly for nice alignment
    myfile << scientific;

    // Step through the vector, and print an element on each line
    for(int i=0; i<x.size(); i++){
        myfile << x[i] << endl;
    }

    // Close the file
    myfile.close();
}


//// Save a vector of vectors to file. This happens a lot, actually.
void save_to_file(string file_path, vector<vector<double>> x){
    // Open a file stream
    ofstream myfile;

    // Open a file on that file stream
    myfile.open(file_path);

    // Set to scientific notation, mostly for alignment
    myfile << scientific;

    // Print each sub-vector to a column.
    for(int i=0; i<x[0].size(); i++) {
        for(int j=0; j<x.size(); j++){
            myfile << x[j][i] << "\t";
        }
        myfile << endl;
    }

    // Close the file
    myfile.close();
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

// Compute mean of a vector
double mean(vector<double> x) {
    return accumulate(x.begin(), x.end(), 0.0) / x.size();
}

// Compute mean of a deque
double mean(deque<double> x) {
    double sum = 0;

    for(deque<double>::iterator j=x.begin(); j!=x.end();++j){
        sum += *j;
    }

    return sum/x.size();
}

// Compute standard deviation of a vector
double stdev(deque<double> x) {
    double mean_val = mean(x);
    double s = 0;

    for(deque<double>::iterator j=x.begin(); j!=x.end();++j){
        s += pow((*j - mean_val), 2.0);
    }

    return sqrt(s/x.size());
}