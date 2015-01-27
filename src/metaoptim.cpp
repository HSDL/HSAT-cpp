#include "../include/metaoptim.hpp"

// Null initializer for search
Search::Search(){}

void Search::parse_param_file(string file_name){
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


void Search::save_settings(string file_name){
    // Open a file stream
    ofstream myfile;

    // Open a file on that file stream
    myfile.open(file_name);

    // Print a file with appropriate data
    myfile << "FUNC    " << p_best.function << endl;
    myfile << "NAGENTS " << p_best.n_agents << endl;
    myfile << "ADAPT   " << p_best.adaptive << endl;
    myfile << "INTER   " << p_best.interacting << endl;
    myfile << "TINIT   " << p_best.temp_init << endl;
    myfile << "DELT    " << p_best.delt << endl;
    myfile << "L_HIST  " << p_best.history_length << endl;
    myfile << "NREPS   " << p_best.n_reps << endl;
    myfile << "MAX_IT  " << p_best.max_iter << endl;
    myfile << "DIMS    " << p_best.D << endl;
    myfile << "UBND    " << p_best.ub << endl;
    myfile << "LBND    " << p_best.lb << endl;

    myfile.close();
}


PatternSearch::PatternSearch(string file_name){
    parse_param_file(file_name);
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
    parse_param_file(file_name);
}

void UnivariateSearch::solve(int max_iter){
    // Define a few initial things
    current_iteration = 0;
    double new_val = 0;
    Parameters p_current;
    cout << "\nBeginning Optimization Routine" << endl;

    // Do some iterations, bro. Get mad optimized.
    while(current_iteration < max_iter) {
        cout << "\tIteration " << current_iteration << endl;
        // Within each iteration, step in each direction
        for (int i = 0; i < var_name.size(); i++) {
            cout << "\t\tComputing " << var_name[i] ;

            // Initialize vectors for regression
            vector<double> X;
            vector<double> Y;
            for (int j = 0; j < p_best.n_reps; j++){
                // Draw a random variable in the param range
                new_val = uniform(var_vals[i]+step_sizes[i], var_vals[i]-step_sizes[i]);
                X.push_back(new_val);

                // Push that variable into the
                p_current = p_best;
                p_current.set_from_pair(var_name[i], new_val);

                // Run a team with that value
                Team T(p_current);
                T.new_start();
                T.solve();
                Y.push_back(T.best_solution.back());
            }
            // Now, perform regression with Y and X
            new_val = quad_max(X, Y);
            p_best.set_from_pair(var_name[i], new_val);
            cout << "\t= " << new_val << endl;
        }
        // Halve the step-sizes
        for(int i=0; i<step_sizes.size(); i++){
            step_sizes[i] /= 2.0;
        }
        current_iteration++;
    }
}