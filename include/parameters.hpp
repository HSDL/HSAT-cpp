#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <string>
#include <vector>
#include <sstream>
#include "utils.hpp"

using namespace std;


class Parameters{
public:
    //// Variables
    // Must be set separately
    static int n_reps;
    static int max_iter;
    static int D;
    static double ub;
    static double lb;
    static string function;

    static bool adaptive;
    static bool interacting;
    static int history_length;
    static int n_agents;
    static double temp_init;
    static double delt;

    //// Functions
    Parameters(void);
    void set_from_file(string file_name);
    void set_from_pair(string name, double x);
    double obj(vector<double> x);

private:
    //nothing yet
};

#endif