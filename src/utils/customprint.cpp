#include "../../include/utils/customprint.hpp"

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