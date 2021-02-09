#ifndef __FIND_ROUTE_H
#define __FIND_ROUTE_H


#include <map>
#include <queue>
#include <istream>
#include <fstream>
#include <iostream>


std::map<std::string, int> inputs;
std::map<std::string, int> h_kassels;

void input_file(std::string filename, std::map<std::string, int> &inputs);
void heuristic_input_file(std::string filename, std::map<std::string, int> &inputs);

#endif