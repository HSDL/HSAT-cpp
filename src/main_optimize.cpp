#include "../include/parameters.hpp"
#include "../include/metaoptim.hpp"

int main(int argc, char *argv[]){

    // Initialize the optimization by readings parameters from file argv1
    PatternSearch PS(argv[1]);

    // Solve it all
    PS.solve(25);

    // Output the final solution set to a file defined by argv2
    PS.save_settings(argv[2]);

    return 0;
}