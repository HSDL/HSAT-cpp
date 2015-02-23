#include "../include/parameters.hpp"
#include "../include/metaoptim.hpp"
#include "../include/utils.hpp"

int main(int argc, char *argv[]){

    // Initialize the optimization by readings parameters from file argv1
    UnivariateSearch US(argv[2]);

    // Solve it all
    US.solve(atoi(argv[1]));

    // Output the final solution set to a file defined by argv2
//    US.save_settings(argv[3]);

    return 0;
}