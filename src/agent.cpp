#include "../include/agent.hpp"

//// Necessary definitions of static vectors for sharing between agents.
vector<double> Agent::all_fx_current;
vector<vector<double>> Agent::all_xx_current;

//// Inline Agent constructor for accessing static vectors
Agent::Agent(void){}

//// Normal agent constructor, take one int
Agent::Agent(int ID, Parameters x){
    p = x;
    // Remember your god-given name!
    id = ID;

    // The beginning is usually the best place to start
    iteration_number = 0;
    Ti = p.temp_init;

    // If you are not the last agent to be instantiated, grow the sharing vectors.
    if(all_fx_current.size() < p.n_agents) {
        all_fx_current.push_back(0.0);
        vector<double> temp(p.D, 0.0);
        all_xx_current.push_back(temp);
    }
}

//// A function that selects a random starting point, and pushes it to other agents.
void Agent::new_start(void){

    // Selecta  random starting point and evaluate it
    x_current = random_vector(p.D, p.ub, p.lb);
    fx_current = p.obj(x_current);

    // Share hte information
    all_fx_current[id] = fx_current;
    all_xx_current[id] = x_current;
}

//// Generated a candidate solution using Cauchy distribution.
vector<double> Agent::candidate_solution(void){
    // Make some variable for use in this function
    vector<double> candidate; // stores the candidate solution
    vector<double> urv;       // A uniform random vector
    vector<double> w;         // Vector of weights across agents
    double wmax;              // Maximum in weight vector
    int j;                    // Index for random draw

    // Random draw to get candidate starting position
    //   IF Interacting: Check out other solutions
    //   ELSE: Start from where you are
    if(p.interacting) {
        w = all_fx_current;
        wmax = vector_max(w);
        for (int i = 0; i < w.size(); i++) {
            w[i] = wmax - w[i];
        }
        j = weighted_choice(w);
        candidate = all_xx_current[j];
    } else{
        candidate = x_current;
    }

    // Draw a uniform random vector for passing to tan function
    urv = random_vector(p.D, M_PI/2.0, -M_PI/2.0);

    // Cycle through, updating dimensions as you go. Analyze each to see if its in the domain
    int NOT_IN_DOMAIN = 0;
    for(int i=0; i<p.D; i++){
        candidate[i] += 0.5*Ti*tan(urv[i]);
        if(abs(candidate[i]) > 10.0){
            NOT_IN_DOMAIN += 1;
        }
    }

    // Recursive.
    //   IF: any dimension was outside the bounds, repeat this function.
    //   ELSE: return candidate
    if(NOT_IN_DOMAIN==0){
        return candidate;
    } else {
        return candidate_solution();
    }
}

//// A function to perform an iteration of SA.
void Agent::iterate(int iter){
    // Make some variable for use in this function
    iteration_number = iter; // Save the god-given iteration as the current iteration
    vector<double> x_cand;   // Vector for saving new candidate solution
    double fx_cand;          // Objective function value of current solution
    double p_accept;                // Probability of accepting new solution

    // Generate a new solution
    x_cand = candidate_solution();
    fx_cand = p.obj(x_cand);

    // If it is better, accept it
    if(fx_cand < fx_current){
        // Save locally
        x_current = x_cand;
        fx_current = fx_cand;
        // Push to other agents
        all_fx_current[id] = fx_current;
        all_xx_current[id] = x_current;
    } else {
        // If not, accept with some probability
        p_accept = exp((fx_current - fx_cand)/Ti);
        if(uniform(0.0, 1.0) < p_accept){
            // Save locally
            x_current = x_cand;
            fx_current = fx_cand;
            // Push to other agents
            all_fx_current[id] = fx_current;
            all_xx_current[id] = x_current;
        }
    }

    //Update the temperature
    update_temp(iter);
}

//// Updates temperature using simple stretched Cauchy schedule.
void Agent::update_temp(int iter){
    // The logic for this function can be confusing. If history_length
    // is positive, a sliding approach is used. If not, intermittent
    // temperature updates are used.
    // IF history_length IS POSITIVE
    //    IF ADAPTIVE
    //        Update Triki with sliding window
    //    ELSE
    //        Update Cauchy
    // ELSE
    //    IF ADAPTIVE
    //        Push temperature into history deque
    //        IF its time to update
    //            Update Triki with isothermal std.
    //            Clear history deque
    //    ELSE
    //        IF its time to update
    //            Update Cauchy temperature

    if(p.history_length > 0) {
        if (p.adaptive) {
            // Update the quality history
            history.push_back(fx_current);

            // If the quality history is too long, pop one out and calculate the update
            if (history.size() > p.history_length) {
                history.pop_front();
                double triki_update = (1 - p.delt * Ti / pow(stdev(history), 2));
                if (triki_update > 0) {
                    Ti *= triki_update;
                }
            }
        } else {
            Ti = p.temp_init / (1 + p.delt * (static_cast <double> (iteration_number)));
        }
    } else {
        bool UPDATE = false;
        if(iter % p.history_length == 0) {
            UPDATE = true;
        }
        if (p.adaptive) {
            // Update the quality history
            history.push_back(fx_current);
            // If its time to update, update teh temperature and clear the cache
            if(UPDATE){
                double triki_update = (1 - p.delt * Ti / pow(stdev(history), 2));
                if (triki_update > 0) {
                    Ti *= triki_update;
                }
                history.clear();
            }

        } else {
            if(UPDATE){
                Ti = p.temp_init / (1 + p.delt * (static_cast <double> (iteration_number)));
            }
        }
    }
}
