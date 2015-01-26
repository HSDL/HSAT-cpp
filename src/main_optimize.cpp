#include "../include/parameters.hpp"
#include "../include/metaoptim.hpp"

int main(int argc, char *argv[]){

    // Initialize the optimization
    PatternSearch PS(argv[1]);

    // Solve it all
    PS.solve(20);
    return 0;
}