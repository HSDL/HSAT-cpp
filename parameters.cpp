#include "parameters.hpp"

//// Need these to make it work
bool Parameters::adaptive;
bool Parameters::interacting;
int Parameters::n_reps;
int Parameters::max_iter;
int Parameters::D;
int Parameters::n_agents;
int Parameters::history_length;
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