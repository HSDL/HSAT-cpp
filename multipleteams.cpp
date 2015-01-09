#include "multipleteams.hpp"

using namespace std;

//// This constructor actually does some things.
MultipleTeams::MultipleTeams(void){
    // Define the vectors that we need with the appropriate length
    vector<double> temp1(p.max_iter/(double)p.n_agents, 0.0);
    vector<vector<double>> temp2(p.n_reps, temp1);
    vector<double> temp3(p.n_reps, 0.0);

    best_solution = temp2;
    cdf = temp3;
}

//// This actually solves the problem LOTS of times.
double MultipleTeams::solve(void){
    seed_time();

    for(int i=0; i<p.n_reps; i++) {
        // Instantiate a new team
        Team T;

        // Give the team a new start
        T.new_start();

        // Solve the problem with the team
        T.solve();

        // Save results
        cdf[i] = vector_min(Agent().all_fx_current);
        best_solution[i] = T.best_solution;
    }

    // Sort the cdf vector
    sort(cdf.begin(), cdf.end());

    // Return the mean solution
    return mean(cdf);
}