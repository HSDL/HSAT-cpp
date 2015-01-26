#include "../include/parameters.hpp"
#include "../include/metaoptim.hpp"
#include "../include/utils.hpp"

int main(int argc, char *argv[]){

    // Initialize the optimization
    PatternSearch PS(argv[1]);

    // Solve it all
     PS.solve(15);

    return 0;
}