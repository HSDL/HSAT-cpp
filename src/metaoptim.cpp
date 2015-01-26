#include "../include/metaoptim.hpp"


PatternSearch::PatternSearch(string file_name){
    // Set the parameters to their current values in the setup file
    p.set_from_file(file_name);

    // Step through the setup file and build parameter lists
    ifstream inputFile(file_name);
    string line;
    string name;
    double temp;
    bool indicator;

    while (getline(inputFile, line))
    {
        // Read a line
        istringstream ss(line);
        ss >> name >> temp >> indicator;

        if(indicator) {
            var_list.push_back(name);
            var_vals.push_back(temp);
            step_sizes.push_back(0.4*temp);
        }
    }
}

void PatternSearch::solve(int max_iter){
    current_iteration = 0;
    cout << "\nBeginning Optimization Routine" << endl;
    while(current_iteration < max_iter){
        // This variable will keep track of whether or not an improvement has been made
        bool IMPROVED = false;
        cout << "\tIteration " << current_iteration << endl;
        for(int i=1; i<var_list.size(); i++){
            for(int j=-1; j<2; j+=2){
                cout << "\t\tTrying " << var_list[i] <<"\t= "<< showpos << j*step_sizes[i] << noshowpos << endl;
            }
        }

        // If no improvement, update the values
        if(!IMPROVED){
            for(int i=0; i<step_sizes.size(); i++){
                step_sizes[i] /= 2.0;
            }
        }

        current_iteration++;
    }
}