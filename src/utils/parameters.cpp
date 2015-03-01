#include "../../include/utils/parameters.hpp"

//// Construct the thing
Parameters::Parameters(void){}

//// Object function of the thing
double Parameters::obj(vector<double> x) {
    if(function == "griewank"){
        return griewank(x);
    } else if(function == "ackley") {
        return ackley(x);
    } else if(function == "rastigrin") {
        return rastigrin(x);
    } else {
        return -1.0;
    }
}

//// Function to read variables from a file
void Parameters::set_from_file(string file_name) {

    ifstream inputFile(file_name);
    string line;
    string name;

    while (getline(inputFile, line))
    {
        istringstream ss(line);

        ss >> name;

        if(name == "FUNC") {
            ss >> function;
            cout << "Function:         "<< function << endl;
        } else if(name == "NAGENTS"){
            ss >> n_agents;
            cout << "Number of agents: "<< n_agents << endl;
        } else if(name == "ADAPT") {
            ss >> adaptive;
            cout << "Adaptive?:        "<< adaptive << endl;
        } else if(name == "INTER") {
            ss >> interacting;
            cout << "Interacting?:     "<< interacting << endl;
        } else if(name == "TINIT") {
            ss >> temp_init;
            cout << "Initial temp:     "<< temp_init << endl;
        } else if(name == "DELT") {
            ss >> delt;
            cout << "Temp factor:      "<< delt << endl;
        } else if(name == "L_HIST") {
            ss >> history_length;
            cout << "History length:   "<< history_length << endl;
        } else if(name == "NREPS") {
            ss >> n_reps;
            cout << "Number of reps:   "<< n_reps << endl;
        } else if(name == "MAX_IT") {
            ss >> max_iter;
            cout << "Max iterations:   "<< max_iter << endl;
        } else if(name == "DIMS") {
            ss >> D;
            cout << "Number of dims:   "<< D << endl;
        } else if(name == "UBND") {
            ss >> ub;
            cout << "Upper bound on x: "<< ub << endl;
        } else if(name == "LBND") {
            ss >> lb;
            cout << "Lower bound on x: "<< lb << endl;
        }
    }
}

//// Shows the current parameters
void Parameters::print_params(void) {
    cout << "Function:         " <<  function       << endl;
    cout << "Number of agents: " <<  n_agents       << endl;
    cout << "Adaptive?:        " <<  adaptive       << endl;
    cout << "Interacting?:     " <<  interacting    << endl;
    cout << "Initial temp:     " <<  temp_init      << endl;
    cout << "Temp factor:      " <<  delt           << endl;
    cout << "History length:   " <<  history_length << endl;
    cout << "Number of reps:   " <<  n_reps         << endl;
    cout << "Max iterations:   " <<  max_iter       << endl;
    cout << "Number of dims:   " <<  D              << endl;
    cout << "Upper bound on x: " <<  ub             << endl;
    cout << "Lower bound on x: " <<  lb             << endl;
}

//// Sets parameters based on a vector
void Parameters::set_from_pair(string name, double x) {
    if(name == "DELT") {
        delt = x;
    } else if(name == "L_HIST"){
        history_length =static_cast <int> (round(x));
    } else if(name == "NAGENTS"){
        n_agents = static_cast <int> (round(x));
    } else if(name == "TINIT"){
        temp_init = x;
    }
}

//// Sets parameters based on a vector
double Parameters::get_from_name(string name) {
    if(name == "DELT") {
        return delt;
    } else if(name == "L_HIST"){
        return history_length;
    } else if(name == "NAGENTS"){
        return n_agents;
    } else if(name == "TINIT"){
        return temp_init;
    }
    return -1;
}

