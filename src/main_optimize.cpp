#include "../include/parameters.hpp"
#include "../include/metaoptim.hpp"

int main(int argc, char *argv[]){

    // Define and set initial parameters
    Parameters p;
    p.read_file(argv[1]);

    // Perform the optimization
    PS = PatternSearch();

    return 1;
}