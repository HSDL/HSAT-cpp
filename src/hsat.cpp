#include "../include/agent_team/multipleteams.hpp"
#include "../include/meta_optim/univariate.hpp"
#include "../include/meta_optim/pattern.hpp"
#include "../include/utils/customprint.hpp"
#include <sys/time.h>

//using namespace std;

int main(int argc, char *argv[]) {
    // Random seed
    seed_time();

    // Start timing the code
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Variables to figure out what's going on
    long double delta;
    int max_iter = 10;
    bool bench = false;
    bool univariate = false;
    bool pattern = false;
    bool found_output = false;
    bool verb = false;
    string input;
    string output;

    // Parse the inputs
    for(int i=1; i < argc; i++) {
        if (string(argv[i]) == "--bench"    || string(argv[i]) == "-b") {
            bench = true;
        }
        if (string(argv[i]) == "--univar"   || string(argv[i]) == "-u") {
            univariate = true;
            i++;
            max_iter = atoi(argv[i]);
        }
        if (string(argv[i]) == "--pattern"  || string(argv[i]) == "-p") {
            pattern = true;
            i++;
            max_iter = atoi(argv[i]);
        }
        if (string(argv[i]) == "--output"   || string(argv[i]) == "-o") {
            i++;
            output = string(argv[i]);
            found_output = true;
        }
        if (string(argv[i]) == "--input"    || string(argv[i]) == "-i") {
            i++;
            input = string(argv[i]);
        }
        if (string(argv[i]) == "--verbose"  || string(argv[i]) == "-v") {
            verb = true;
        }
    }

    // If no arguments, provide help text
    if(argc == 1){
        cout << "." << endl;
    }

    // Run benchmarking
    if(bench){
        long double fxmean = 0;

        // Initialize it
        MultipleTeams MT(input);

        // Print parameters if verbose
        if(verb){
            MT.p.print_params();
        }

        // Solve it
        fxmean = MT.solve();

        // Print output if requested
        cout << endl << "mean solution = " << fxmean << endl << endl;
        if(verb){
            cout << "all solutions = " << endl;
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

        // If verbose, print beginning values
        if(verb){
            US.p_best.print_params();
        }

        // Solve it all
        US.solve(max_iter, verb);

        // Output the final solution set to a file defined by argv2
        if(found_output) {
            US.save_settings(output);
        }

    }

    // Run pattern search
    if(pattern){
        // Make it
        PatternSearch PS(input);

        // If verbose, print beginning values
        if(verb){
            PS.p_best.print_params();
        }

        // Solve it all
        PS.solve(max_iter, verb);

        // Output the final solution set to a file defined by argv2
        if(found_output) {
            PS.save_settings(output);
        }
    }

    // Take finished time and print duration
    gettimeofday(&end, NULL);
    delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

    cout.precision(2);
    cout << fixed << delta << " seconds elapsed." << endl;

    return 0;
}
