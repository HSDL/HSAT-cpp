#ifndef SEARCH_HPP
#define SEARCH_HPP

using namespace std;

class Search {
public:
    Search();
    void parse_param_file(string file_name);
    void save_settings(string file_name);

    //// Variables
    Parameters p_best;       // The parameters of the simulation
    vector<string> var_name;
    vector<double> var_vals;
    vector<double> lower_lims;
    vector<double> upper_lims;
    vector<double> step_sizes;
};

#endif