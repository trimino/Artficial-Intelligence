#include "find_route.h"
#include <regex>
#include <sstream>


// Parses through the input file and insers entries to a map with locations and respective costs 
void input_file(std::string filename, std::map<std::string, int> &inputs){
    std::ifstream inf {filename};

    if (!inf)
        std::cerr << "Could not read in " << filename << std::endl;

    std::string name;
    std::string lname;
    int cost;
    while (inf){
        std::string line;
        std::getline(inf, line);

        std::stringstream ss(line);
        ss >> name >> lname >> cost;
        name = name + " " + lname;
        if (name != "END OF") inputs.insert( {name, cost} );     
    }
}



// Parses through the heuristic file and adds entries to the map 
void heuristic_input_file(std::string filename, std::map<std::string, int> &inputs){
    std::ifstream inf {filename};

    if (!inf)
        std::cerr << "Could not read in " << filename << std::endl;

    std::string name;
    int cost;
    while (inf){
        std::string line;
        std::getline(inf, line);

        std::stringstream ss(line);
        ss >> name >> cost;
        if (name != "END") inputs.insert( {name, cost} );
    }
}

int main (int argc, char** argv){
    std::map<std::string, int> inputs;
    std::map<std::string, int> heuristics;

    input_file("input1.txt", inputs);
    heuristic_input_file("h_kassel.txt", heuristics);

    std::cout << heuristics.at("Bristol") << std::endl;
    
    return EXIT_SUCCESS;
}