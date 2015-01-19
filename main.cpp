#include "utils.hpp"
#include "parameters.hpp"
#include "multipleteams.hpp"


int main(int argc, char *argv[]) {

    // Define and  set parameters
    Parameters p;
    p.read_file(argv[1]);

    // Solve and print results
    MultipleTeams MT;
    print(MT.solve());
    print(MT.cdf);

    // Save results to file
    save_to_file(argv[2], MT.best_solution);

    return 1;
}