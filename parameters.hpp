#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <string>
#include <vector>

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

    // Set by call to function
    static bool adaptive;
    static bool interacting;
    static int n_agents;
    static int dwell;
    static double temp_init;
    static double delt;

    //// Functions
    Parameters(void);
    void set_namasa(void);
    void set_napasa(void);
    void set_nasasa(void);
    void set_aamasa(void);
    void set_aapasa(void);
    void set_aasasa(void);
    double obj(vector<double>);

private:
    //nothing yet
};

#endif