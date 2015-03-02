#include "../include/agent_team/multipleteams.hpp"
#include "../include/meta_optim/univariate.hpp"
#include "../include/meta_optim/pattern.hpp"
#include "../include/utils/customprint.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    // Variables to figure out what's going on
    bool bench = false;
    bool univariate = false;
    bool pattern = false;
    int max_iter = 10;
    bool found_output = false;
    bool verb = false;
    string input;
    string output;

    // Parse the inputs
    for(int i=1; i < argc; i++) {
        if (string(argv[i]) == "--bench"   || string(argv[i]) == "-b") {
            bench = true;
        }
        if (string(argv[i]) == "--univar"  || string(argv[i]) == "-u") {
            univariate = true;
            i++;
            max_iter = atoi(argv[i]);
        }
        if (string(argv[i]) == "--pattern" || string(argv[i]) == "-p") {
            pattern = true;
            i++;
            max_iter = atoi(argv[i]);
        }
        if (string(argv[i]) == "--output"  || string(argv[i]) == "-o") {
            i++;
            output = string(argv[i]);
            found_output = true;
        }
        if (string(argv[i]) == "--input"   || string(argv[i]) == "-i") {
            i++;
            input = string(argv[i]);
        }
        if (string(argv[i]) == "--verbose" || string(argv[i]) == "-v") {
            verb = true;
        }
    }

    // If no arguments, provide help text
    if(argc == 1){
        cout << "You probably need help. RTFM." << endl;
    }

    // Run benchmarking
    if(bench){
        // Initialize and solve
        MultipleTeams MT(input);
        MT.solve();

        // Print output if requested
        if(verb){
            print(MT.solve());
            print(MT.cdf);
        }

        // Save output if possible
        if(found_output){
            save_to_file(output, MT.best_solution);
        }
    }

    // Run stochastic univariate search
    if(univariate){
        // Make it
        UnivariateSearch US(input);

        // Solve it all
        US.solve(max_iter);

        // Output the final solution set to a file defined by argv2
        if(found_output) {
            US.save_settings(output);
        }

    }

    // Run pattern search
    if(pattern){
        // Make it
        PatternSearch PS(input);

        // Solve it all
        PS.solve(max_iter);

        // Output the final solution set to a file defined by argv2
        if(found_output) {
            PS.save_settings(output);
        }
    }

    return 0;
}