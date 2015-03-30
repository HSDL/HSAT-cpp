#include "../include/agent_team/multipleteams.hpp"
#include "../include/meta_optim/univariate.hpp"
#include "../include/meta_optim/pattern.hpp"
#include "../include/utils/customprint.hpp"
#include <sys/time.h>
#include <omp.h>

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
    bool found_input = false;
    bool verb = false;
    string input;
    string output;

    // Parse the inputs
    for(int i=1; i < argc; i++) {
        if      (string(argv[i]) == "--bench"    || string(argv[i]) == "-b") {
            bench = true;
        }
        else if (string(argv[i]) == "--univar"   || string(argv[i]) == "-u") {
            univariate = true;
            i++;
            max_iter = atoi(argv[i]);
        }
        else if (string(argv[i]) == "--pattern"  || string(argv[i]) == "-p") {
            pattern = true;
            i++;
            max_iter = atoi(argv[i]);
        }
        else if (string(argv[i]) == "--output"   || string(argv[i]) == "-o") {
            i++;
            output = string(argv[i]);
            found_output = true;
        }
        else if (string(argv[i]) == "--input"    || string(argv[i]) == "-i") {
            i++;
            input = string(argv[i]);
            found_input = true;
        }
        else if (string(argv[i]) == "--verbose"  || string(argv[i]) == "-v") {
            verb = true;
        }
        else if (string(argv[1]) == "--help"     || string(argv[i]) == "-h" || argc == 1) {
            cout << "                                                                          " << endl;
            cout << "HSAT                                                                      " << endl;
            cout << "    Usage: hsat [OPTION]...                                               " << endl;
            cout << "    Implements the Heterogenous Simulated Annealing Teams Algorithm.      " << endl;
            cout << "                                                                          " << endl;
            cout << "OPTIONS                                                                   " << endl;
            cout << "   -b,      --bench           Benchmark the given parameters, by solving  " << endl;
            cout << "                              the function a number of times.             " << endl;
            cout << "   -u N,    --univar N        Meta-optimization using stochastic          " << endl;
            cout << "                              univariate search over N iterations.        " << endl;
            cout << "   -p N,    --pattern N       Meta-optimization using a pattern search    " << endl;
            cout << "                              over N iterations.                          " << endl;
            cout << "   -i FILE, --input FILE      Input file name (syntax defined below).     " << endl;
            cout << "   -o FILE, --output FILE     Output file name.                           " << endl;
            cout << "   -v,      --verbose         Print intermittent information during       " << endl;
            cout << "                              solving.                                    " << endl;
            cout << "                                                                          " << endl;
            cout << "BENCHMARKING SYNTAX                                                       " << endl;
            cout << "   A benchmarking text file serves as the input file for the --bench flag." << endl;
            cout << "   The syntax consists of keyword/value pairs on unique lines. A list of  " << endl;
            cout << "   the necessary keywords and their allowable values are provided below.  " << endl;
            cout << "      KEYWORD    VALUE       NOTE                                         " << endl;
            cout << "      FUNC       ackley      asdf                                         " << endl;
            cout << "                 griewank    asdf                                         " << endl;
            cout << "                 rastigrin   asdf                                         " << endl;
            cout << "      ADAPT      0           asdf                                         " << endl;
            cout << "                 1           asdf                                         " << endl;
            cout << "      INTER      0           asdf                                         " << endl;
            cout << "                 1           asdf                                         " << endl;
            cout << "      NREPS      positive    asdf                                         " << endl;
            cout << "      MAX_IT     positive    asdf                                         " << endl;
            cout << "      DIMS       positive    asdf                                         " << endl;
            cout << "      UBND       real        asdf                                         " << endl;
            cout << "      LBND       real        Must be less than the value assigned to UBND." << endl;
            cout << "      NAGENTS    positive    asdf                                         " << endl;
            cout << "      TINIT      positive    asdf                                         " << endl;
            cout << "      DELT       positive    asdf                                         " << endl;
            cout << "      L_HIST     positive    asdf                                         " << endl;
            cout << "                 negative    asdf                                         " << endl;
            cout << "                                                                          " << endl;
            cout << "META OPTIMIZATION SYNTAX                                                  " << endl;
            cout << "   A meta-optimization text file serves as the input file for the --univar" << endl;
            cout << "   flag and --pattern flag. The syntax is nearly identical to that used   " << endl;
            cout << "   for benchmarking, and the same keywords are required. The main         " << endl;
            cout << "   difference is that every keyword/value pair is followed by a 0 or 1    " << endl;
            cout << "   (indicating if the parameter should be tuned) and then two more values," << endl;
            cout << "   specifying a lower and upper bound. See examples below.                " << endl;
            cout << "      KEYWORD  VALUE  BOOL  LOWER_BOUND  UPPER_BOUND                      " << endl;
            cout << "      DELT     0.1    1     1e-10        100.0                            " << endl;
            cout << "      MAX_IT   10000  0                                                   " << endl;
            cout << "                                                                          " << endl;
            return 0;
        }
        else {
            cout << "hsat: Invalid option, '" << string(argv[i]) << "' is not recognized. Try running 'hsat --help' for help text." << endl;
            return 1;
        }
    }

    // Make sure there's an input file
    if(!found_input) {
        cout << "hsat: An input file was not provided, but is required for --bench, --univariate, and --pattern." << endl;
        return 1;
    }

    // Run benchmarking
    if(bench){
        // Initialize it
        MultipleTeams MT(input);

        // Print parameters if verbose
        if(verb){
            MT.p.print_params();
        }

        // Print output if requested
        cout << endl << "mean solution = " << MT.solve() << endl << endl;
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
