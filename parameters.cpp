#include "parameters.hpp"

//// Need these to make it work
bool Parameters::adaptive;
bool Parameters::interacting;
int Parameters::n_reps;
int Parameters::max_iter;
int Parameters::D;
int Parameters::n_agents;
int Parameters::dwell;
double Parameters::ub;
double Parameters::lb;
double Parameters::temp_init;
double Parameters::delt;
string Parameters::function;

//// Construct the thing
Parameters::Parameters(void){}

//// Object function of the thing
double Parameters::obj(vector<double> x) {
    if(function == "griewank"){
        return griewank(x);
    } else if(function == "ackley") {
        return ackley(x);
    } else if(function == "rastigrin") {
        return rastigrin(x);
    } else {
        return -1.0;
    }
}

//// Set non-adaptive MSA parameters
void Parameters::set_namasa(void){
    adaptive = false;
    interacting = true;
    n_agents = 6;

    temp_init = 2.4;
    delt = 0.2;
    dwell = 1;
}

//// Set non-adaptive SA parameters
void Parameters::set_nasasa(void){
    adaptive = false;
    interacting = false;
    n_agents = 1;

    temp_init = 0.4284;
    delt = 0.02633;
    dwell = 1;
}


void set_napasa(void){
    // asdf
}

void set_aamasa(void){
    // asdf
}

void set_aapasa(void){
    // asdf
}

void set_aasasa(void){
    // asdf
}