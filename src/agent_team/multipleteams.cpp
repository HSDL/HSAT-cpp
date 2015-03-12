#include "../../include/agent_team/multipleteams.hpp"

using namespace std;

// This does the things, and initializes p from file
MultipleTeams::MultipleTeams(Parameters x){
    // Read from a file
    p = x;

    // Define the vectors that we need with the appropriate length
    vector<double> temp1(static_cast <unsigned long> (p.max_iter/(double)p.n_agents), 0.0);
    vector<vector <double> > temp2(static_cast <unsigned long> (p.n_reps), temp1);
    vector<double> temp3(static_cast <unsigned long> (p.n_reps), 0.0);

    best_solution = temp2;
    cdf = temp3;
}

// This does the things, and initializes p from file
MultipleTeams::MultipleTeams(string file_name){
    // Read from a file
    p.set_from_file(file_name);

    // Define the vectors that we need with the appropriate length
    vector<double> temp1(static_cast <unsigned long> (p.max_iter/(double)p.n_agents), 0.0);
    vector< vector<double> > temp2(static_cast <unsigned long> (p.n_reps), temp1);
    vector<double> temp3(static_cast <unsigned long> (p.n_reps), 0.0);

    best_solution = temp2;
    cdf = temp3;
}

//// This actually solves the problem LOTS of times.
double MultipleTeams::solve(void){
    seed_time();

    // Make a vector of teams
    vector<Team> team_list;
    for(int i=0; i<p.n_reps; i++) {
        Team temp(p);
        team_list.push_back(temp);
    }

    // Give each team a new start
    for(int i=0; i<p.n_reps; i++) {
        // Give the team a new start
        team_list[i].new_start();
    }

    // Run the solution loop in parallel
    # pragma omp parallel for
    for(int i=0; i<p.n_reps; i++) {
        // Solve the problem with the team
        team_list[i].solve();
    }

    // Save results
    for(int i=0; i<p.n_reps; i++) {
        cdf[i] = team_list[i].best_solution.back();
        best_solution[i] = team_list[i].best_solution;
    }

    // Sort the cdf vector
    sort(cdf.begin(), cdf.end());

    // Return the mean solution
    return mean(cdf);
}