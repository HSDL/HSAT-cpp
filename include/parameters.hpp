#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <string>
#include <vector>
#include <sstream>
#include "utils/objective.hpp"

using namespace std;


class Parameters{
public:
    //// Variables
    // Must be set separately
    int n_reps;
    int max_iter;
    int D;
    double ub;
    double lb;
    string function;

    bool adaptive;
    bool interacting;
    int history_length;
    int n_agents;
    double temp_init;
    double delt;

    //// Functions
    Parameters(void);
    void set_from_file(string file_name);
    void set_from_pair(string name, double x);
    void print_params(void);
    double get_from_name(string name);
    double obj(vector<double> x);

private:
    //nothing yet
};

#endif