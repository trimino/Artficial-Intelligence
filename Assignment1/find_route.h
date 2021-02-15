#ifndef __FIND_H
#define __FIND_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <queue>
#include <iomanip>


class Node{

    public:
        Node();
        Node(Node* parent, std::string state, float pathCost, float totalCost);
        Node(const Node& node);

        float get_pathCost();
        float get_totalCost();
        
        std::string get_state();
        void set_state(std::string state);

        Node* get_parent();
        void set_parent(Node* parent);

        friend bool operator<(const Node &n1, const Node &n2);
    
    private:
        float       _totalCost;
        float       _pathCost;
        std::string _state;
        Node*       _parent;
};


class CompareMyNodePtr{
    public:
        bool operator() (Node* left, Node* right);
};


Node* informed_search(std::string start, std::string dest, std::multimap<std::string, std::pair<std::string, float>> data, std::map<std::string, float> heuristics, int &nodes_generated, int &nodes_expanded);

void expand(Node* node, std::priority_queue<Node*, std::vector<Node*>, CompareMyNodePtr> &frontier, std::multimap<std::string, std::pair<std::string, float>> actions, int &n_gen);

Node* uninformed_search(std::string start, std::string dest, std::multimap<std::string, std::pair<std::string, float>> data, int &nodes_generated, int &nodes_expanded);

void read_input_file(std::string filename, std::multimap<std::string, std::pair<std::string, float>> &data);

void read_heuristic_file(std::string filename, std::map<std::string, float> &heuristic);

Node* create_node(Node &parent, std::string availableCity, float pathCost);

bool is_explored(std::vector<std::string> explored, std::string state);

bool is_queue(std::vector<Node> frontier, Node current);

Node* reverse(Node* head);

#endif