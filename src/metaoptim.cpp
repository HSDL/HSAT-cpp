#include "../include/metaoptim.hpp"
#include "stats.hpp"

// Null initializer for search
Search::Search(){seed_time();}

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
            step_sizes.push_back(0.25*temp);
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
    seed_time();
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
    seed_time();
    parse_param_file(file_name);
}

void UnivariateSearch::solve(int max_iter){
    // Stores the current iteration and values
    current_iteration = 0;
    Parameters p_current;
    // Stores a new value
    double new_val = 0;
    // Keeps track of whether or not an edge solution has been found
    bool EDGE_SOLUTION;
    // Keeps track of whether a bound is being approached
    bool APPROACHING_BOUND;
    // Stores values to feed to quadratic regression
    vector<double> X;
    vector<double> Y;
    // Stores the results from the quadratic regression
    vector<double> quad_res;
    double temp_ub;
    double temp_lb;
    cout << "\nBeginning Optimization Routine" << endl;

    // Do some iterations, bro. Get mad optimized.
    while(current_iteration < max_iter) {
        cout << "\tIteration " << current_iteration << endl;
        EDGE_SOLUTION = false;
        APPROACHING_BOUND = false;
        // Within each iteration, step in each direction
        for (int i = 0; i < var_name.size(); i++) {
            cout << "\t\tComputing " << var_name[i];

            // Draw a random variable in the param range
            temp_ub = min(var_vals[i]+step_sizes[i], upper_lims[i]);
            temp_lb = max(var_vals[i]-step_sizes[i], lower_lims[i]);

            // Check to see if we're up against a bound
            if(temp_ub == upper_lims[i] || temp_lb == lower_lims[i]){
                APPROACHING_BOUND = true;
            }

            // Initialize vectors for regression
            for (int j = 0; j < p_best.n_reps; j++){

                // Define a new value
                new_val = uniform(temp_ub, temp_lb);

                // Create a parameter set with the new value
                p_current = p_best;
                p_current.set_from_pair(var_name[i], new_val);
//                p_current.print_params();

                // Save the new value (this takes advantage of rounding when pushed to parameter set
                // X.push_back(new_val);
                X.push_back(p_current.get_from_name(var_name[i]));

                // Run a team with that value
                Team T(p_current);
                T.new_start();
                T.solve();
                Y.push_back(log10(T.best_solution.back()));
            }

            // Now, perform regression with Y and X
            quad_res = quad_max(X, Y);
            if(quad_res[3] > 0.01) {
                p_best.set_from_pair(var_name[i], quad_res[0]);
                var_vals[i] = p_best.get_from_name(var_name[i]);
                // Check to see if we're against a non-limiting edge solution
                if (quad_res[0] == vector_min(X) || quad_res[0] == vector_max(X)){
                    if (!APPROACHING_BOUND) {
                        EDGE_SOLUTION = true;
                    }
                }
            }

            cout << "\t= " << quad_res[0]
                    << ", mean = " << quad_res[2]
                    << ", fx = "   << quad_res[1]
                    << ", r2 = "   << quad_res[3]
                    << ", "        << (quad_res[3] > 0.01)
                    << ", "        << EDGE_SOLUTION << endl;

            X.clear();
            Y.clear();
        }
        // Halve the step-sizes
        if(!EDGE_SOLUTION) {
            for (int i = 0; i < step_sizes.size(); i++) {
                step_sizes[i] /= 2.0;
            }
            cout << "\t\t" << "Updating step sizes." << endl;
        }
        current_iteration++;
    }
}