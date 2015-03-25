#include "../../include/agent_team/team.hpp"

//// This constructs the team
Team::Team(Parameters x){
    p = x;
    // Make a vector of the appropriate length for storing things.
    vector<double> temp(static_cast <unsigned long> (p.max_iter/(static_cast <double> (p.n_agents))), 0.0);
    best_solution = temp;
}

//// Give the team a new start
void Team::new_start(void){
    // Reset the vector for sharing the best solutions
    agent_list[0].all_fx_current.clear();
    agent_list[0].all_xx_current.clear();

    // Create agent list
    for(int i=0; i<p.n_agents; i++){
        Agent a(i, p);
        agent_list.push_back(a);
    }

    // Give agents starting locations
    for(int i=0; i<p.n_agents; i++){
        agent_list[i].new_start();
    }

    // Save the first best solution
    best_solution[0] = vector_min(agent_list[0].all_fx_current);
};

////// Iterate the team
//void Team::iterate(int iter){
//    // Iterate each agent
//    for(int i=0; i<agent_list.size(); i++){
//        agent_list[i].iterate(iter);
//    }
//
//    // Share new results between agents
//    for(int i=0; i<agent_list.size(); i++){
//        agent_list[0].all_fx_current[agent_list[i].id] = agent_list[i].fx_current;
//        agent_list[0].all_xx_current[agent_list[i].id] = agent_list[i].x_current;
//    }
//
//    if (p.n_reps == 1){
//        cout << endl;
//    }
//}

//// Iterate the team
void Team::iterate(int iter){
    // Iterate each agent
    for(int i=0; i<agent_list.size(); i++){
        agent_list[i].iterate(iter);
    }
    if (p.n_reps == 1){
        cout << endl;
    }
}


//// Solve the team
void Team::solve(void){
    // Iterate many times, and save the best solution each time
    for(int i=1; i<p.max_iter/(double)p.n_agents; i++){
        // Do the iteration
        iterate(i);

        // Save the best solution
        best_solution[i] = vector_min(agent_list[0].all_fx_current);

        // If it isn't better than last time, overwrite
        if(best_solution[i] > best_solution[i-1]){
            best_solution[i] = best_solution[i-1];
        }
    }
}