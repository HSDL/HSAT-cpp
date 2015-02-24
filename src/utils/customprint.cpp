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
