#include "../../include/agent_team/multipleteams.hpp"

using namespace std;

// This does the things, and initializes p from file
MultipleTeams::MultipleTeams(Parameters x){
    // Save the parameters
    p = x;

    // Define the vectors that we need with the appropriate length
    vector<long double> temp1(static_cast <unsigned long> (p.max_iter/(long double)p.n_agents), 0.0);
    vector<vector <long double> > temp2(static_cast <unsigned long> (p.n_reps), temp1);
    vector<long double> temp3(static_cast <unsigned long> (p.n_reps), 0.0);

    // Initialize the best solution and cdf vectors
    best_solution = temp2;
    cdf = temp3;
}

// This does the things, and initializes p from file
MultipleTeams::MultipleTeams(string file_name){
    // Read from a file
    p.set_from_file(file_name);

    // Define the vectors that we need with the appropriate length
    vector<long double> temp1(static_cast <unsigned long> (p.max_iter/(long double)p.n_agents), 0.0);
    vector< vector<long double> > temp2(static_cast <unsigned long> (p.n_reps), temp1);
    vector<long double> temp3(static_cast <unsigned long> (p.n_reps), 0.0);

    best_solution = temp2;
    cdf = temp3;
}

//// This actually solves the problem LOTS of times.
long double MultipleTeams::solve(void){

    for(int i = 0; i<p.n_reps; i++) {
        // Instantiate a new team
        Team T(p);

        // Give the team a new start
        T.new_start();

        // Solve the problem with the team
        T.solve();

        // Save results
        cdf[i] = T.best_solution.back();
        best_solution[i] = T.best_solution;
    }

    // Sort the cdf vector
    sort(cdf.begin(), cdf.end());

    // Return the mean solution
    return mean(cdf);
}