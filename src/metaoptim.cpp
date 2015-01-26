#include "../include/metaoptim.hpp"


PatternSearch::PatternSearch(string file_name){
    // Set the parameters to their current values in the setup file
    p_best.set_from_file(file_name);

    // Step through the setup file and build parameter lists
    ifstream inputFile(file_name);
    string line;
    string name;
    double lower_limit;
    double upper_limit;
    double temp;
    bool indicator;

    while (getline(inputFile, line))
    {
        // Read a line
        istringstream ss(line);
        ss >> name >> temp >> indicator;

        if(indicator) {
            ss >> lower_limit;
            lower_lims.push_back(lower_limit);
            ss >> upper_limit;
            upper_lims.push_back(upper_limit);
            var_name.push_back(name);
            var_vals.push_back(temp);
            step_sizes.push_back(0.4*temp);
        }
    }
}

void PatternSearch::solve(int max_iter){
    // Do some initial things
    current_iteration = 0;
    double fx_current;
    double new_val;
    bool IMPROVED;
    Parameters p_current;

    // Find average initial quality
    MultipleTeams MT(p_best);
    fx_best = MT.solve();
    cout << "\nBeginning Optimization Routine, fx = " << fx_best << endl;

    while(current_iteration < max_iter){
        // This variable will keep track of whether or not an improvement has been made
        IMPROVED = false;
        cout << "\tIteration " << current_iteration << endl;
        for(int i=0; i<var_name.size(); i++){
            for(int j=1; j>-2; j-=2){
                // Modify the list of parameters
                p_current = p_best;
                new_val = var_vals[i] + j*step_sizes[i];
                // Keep it all in range
                if(new_val < lower_lims[i]){
                    new_val = lower_lims[i];
                }
                if(new_val > upper_lims[i]){
                    new_val = upper_lims[i];
                }
                cout << "\t\tTrying " << var_name[i] <<"\t= "<< new_val << ", ";
                p_current.set_from_pair(var_name[i], new_val);

                // Evalute the new combination
                MultipleTeams MT(p_current);
                fx_current = MT.solve();
                cout << "fx = " << fx_current << endl;

                // Keep track of the best solution
                if(fx_current < fx_best){
                    cout << "\t\tImprovement" << endl;
                    var_vals[i] = new_val;
                    fx_best = fx_current;
                    p_best = p_current;
                    IMPROVED = true;
                    i = 100000;
                    j = -100000;
                }
            }
        }

        // If no improvement, update the stepsize values
        if(!IMPROVED){
            cout << "\t\tUpdating stepsizes" << endl;
            for(int i=0; i<step_sizes.size(); i++){
                step_sizes[i] /= 2.0;
            }
        }
        current_iteration++;
    }
}

UnivariateSearch::UnivariateSearch(string file_name){
    // Set the parameters to their current values in the setup file
    p_best.set_from_file(file_name);

    // Step through the setup file and build parameter lists
    ifstream inputFile(file_name);
    string line;
    string name;
    double lower_limit;
    double upper_limit;
    double temp;
    bool indicator;

    while (getline(inputFile, line))
    {
        // Read a line
        istringstream ss(line);
        ss >> name >> temp >> indicator;

        if(indicator) {
            ss >> lower_limit;
            lower_lims.push_back(lower_limit);
            ss >> upper_limit;
            upper_lims.push_back(upper_limit);
            var_name.push_back(name);
            var_vals.push_back(temp);
            step_sizes.push_back(0.4*temp);
        }
    }
}