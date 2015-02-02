#include "../include/utils.hpp"

#define PI 3.141592653589793

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
    // Initialize a couple variable for sums
    double fx = 0;

    // Step through every dimensions and do a thing
    for(int i=0; i < x.size(); i++){
        fx += x[i]*x[i] - 10*cos(2*PI*x[i]) + 10;
    }

    // Return a sum of sums
    return fx;
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

// Compute the x value fo the optimium of a linear regression
vector<double> quad_max(vector<double> x, vector<double> y){
    // Initialize things
    vector<double> Y(4, 0);
    vector<vector<double>> A(3, Y);
    double n = 0;
    double x1 = 0;
    double x2 = 0;
    double x3 = 0;
    double x4 = 0;
    double y1 = 0;
    double yx1 = 0;
    double yx2 = 0;

    // Calculate some sums that will be necessary
    for(int i=0; i < x.size(); i++) {
        n += 1;
        x1 += x[i];
        x2 += x[i]*x[i];
        x3 += x[i]*x[i]*x[i];
        x4 += x[i]*x[i]*x[i]*x[i];
        y1 += y[i];
        yx1 += y[i]*x[i];
        yx2 += y[i]*x[i]*x[i];
    }

    // Make a matrix
    A[0][0] = n;
    A[1][0] = x1;
    A[0][1] = x1;
    A[0][2] = x2;
    A[1][1] = x2;
    A[2][0] = x2;
    A[1][2] = x3;
    A[2][1] = x3;
    A[2][2] = x4;
    A[0][3] = y1;
    A[1][3] = yx1;
    A[2][3] = yx2;

    n = 3;

    for (int i=0; i<n; i++) {
        // Search for maximum in this column
        double max_elem = abs(A[i][i]);
        int max_row = i;
        for (int k=i+1; k<n; k++) {
            if (abs(A[k][i]) > max_elem) {
                max_elem = abs(A[k][i]);
                max_row = k;
            }
        }

        // Swap maximum row with current row (column by column)
        for (int k=i; k<n+1;k++) {
            double temp = A[max_row][k];
            A[max_row][k] = A[i][k];
            A[i][k] = temp;
        }

        // Make all rows below this one 0 in current column
        for (int k=i+1; k<n; k++) {
            double c = -A[k][i]/A[i][i];
            for (int j=i; j<n+1; j++) {
                if (i==j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] += c * A[i][j];
                }
            }
        }
    }

    // Solve equation Ax=b for an upper triangular matrix A
    vector<double> xx(n);
    for (int i=n-1; i>=0; i--) {
        xx[i] = A[i][n]/A[i][i];
        for (int k=i-1;k>=0; k--) {
            A[k][n] -= A[k][i] * xx[i];
        }
    }

    // Check to make sure the equation is concave up
    double x_loc;
    if(xx[2] > 0){
        x_loc = -xx[1]/(2*xx[2]);
    } else {
        double x_min = vector_min(x);
        double x_max = vector_max(x);

        if ((xx[0] + x_min*xx[1] +x_min*x_min*xx[2]) >
                (xx[0] + x_max*xx[1] +x_max*x_max*xx[2]) ) {
            x_loc = x_max;
        } else {
            x_loc = x_min;
        }
    }

    double fx = xx[0] + x_loc*xx[1] +x_loc*x_loc*xx[2];
    vector<double> results;
    results.push_back(x_loc);
    results.push_back(fx);

    return results;

}
