#include "../include/metaoptim.hpp"


PatternSearch::PatternSearch(void){}

void PatternSearch::set_from_file(string file_name){
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
    print(max_iter);
}