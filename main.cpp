#include "utils.hpp"
#include "parameters.hpp"
#include "multipleteams.hpp"
#include <string>
#include <iostream>
#include <fstream>


int main(void) {

    // Define and  set parameters
    Parameters p;
    p.function = "griewank";
    p.adaptive = false;
    p.interacting = false;
    p.n_agents = 1;
    p.temp_init = 0.4284;
    p.delt = 0.02633;
    p.n_reps = 10;
    p.max_iter = 30000;
    p.D = 30;
    p.ub = 10;
    p.lb = -10;

    // Define location to save results
    string file_name = "/Users/IDIG/Desktop/asdf.txt";

    // Solve and print results
    MultipleTeams MT;
    print(MT.solve());
    print(MT.cdf);

    // Save results to file
    save_to_file(file_name, MT.best_solution);

    return 1;

}