#include "find_route.h"

Node::Node(): _parent{NULL}, _state{"NULL"}, _pathCost{0.0}, _totalCost{0.0}{
    // Empty Constructor
}

Node::Node(Node* parent, std::string state, float pathCost, float totalCost): _parent{parent}, _state{state}, _pathCost{pathCost}, _totalCost{totalCost}{
    // Constructor for Node
}

Node::Node(const Node &node): _parent{node._parent}, _state{node._state}, _pathCost{node._pathCost}, _totalCost{node._totalCost}{
    // Cop Constructor for Node
}

float Node::get_pathCost(){
    return this->_pathCost;
}

float Node::get_totalCost(){
    return this->_totalCost;
}
        
std::string Node::get_state(){
    return this->_state;
}

void Node::set_state(std::string state){
    this->_state = state;
}

Node* Node::get_parent(){
    return this->_parent;
}

void Node::set_parent(Node* parent){
    this->_parent = parent;
}

bool operator<(const Node &n1, const Node &n2){
    // Object with the least value will be on the top
    return n1._pathCost > n2._pathCost;
}


/*
Name        : read_input_file
Parameters  : Reference multimap that uses a string as a key to hold all possible actions for the current state and the filename where the data is store 
Description : Reads in the problem data into a multimap to be used in informed and uninformed search
Returns     : Void
*/
void read_input_file(std::string filename, std::multimap<std::string, std::pair<std::string, float> > &data){
    std::ifstream ifs {filename};
    if (!ifs)
        std::cerr << "Could not read in file: " << filename << std::endl;
    
    std::string src;
    std::string dest;
    std::string cost;
    float pathCost;

    while (ifs){
        std::string line;
        std::getline(ifs, line);
        std::stringstream ss (line);
        ss >> src >> dest >> pathCost;
        
        if (src != "END")
            data.insert({src, std::make_pair(dest, pathCost)});
        
    }   
}


/*
Name        : read_heuristic_file
Parameters  : A reference to a map to be populated with a key that is type string and value for heuristic value for that key
Description : Populates the map and brings the heuristic values into code to be used for informed searches
Returns     : Void
*/
void read_heuristic_file(std::string filename, std::map<std::string, int> &h){
    std::ifstream ifs {filename};
    if (!ifs)
        std::cerr << "Could not read in file: " << filename << std::endl;
    
    std::string city;
    float cost;
    while (ifs){
        std::string line;
        std::getline(ifs, line);
        std::stringstream ss(line);
        
        ss >> city >> cost;
        if (city != "END")
            h.insert({city, cost});
    }
    
}


/*
Name        : create_node
Parameters  : Parent node to child (referenced), the avaiableCity is one of the actions that the parent can take, pathcost is the cost of getting there to the parent
Description : Create a new node 
Returns     : A pointer to the new node
*/
Node* create_node(Node &parent, std::string avaialableCity, float pathCost){
    Node *child = new Node{&parent, avaialableCity, pathCost, parent.get_totalCost() + pathCost};
    return child;
}


/*
Name    : is_explored
Parameters  : A vector of strings that represent the nodes that have been explored and the successors of the current state
Description : Check to see if a city has been explored
Returns     : Returns a bool (true if it has been explored)
*/
bool is_explored(std::vector<std::string> explored, std::string state){
    for (int i = 0; i < explored.size(); ++i){
        if (explored.at(i) == state)
            return true;
    }
    return false;
}


Node* uninformed_search(std::string start, std::string dest, std::multimap<std::string, std::pair<std::string, float>> data, int &nodes_generated, int &nodes_expanded){
    Node* startNode= new Node {NULL, start, 0.0, 0.0};

    std::priority_queue <Node*> frontier;
    std::vector<std::string> explored;
    frontier.push(startNode);

    while (!frontier.empty()){
        // Chooses the lowest cost node in frontier
        Node* nodePop = frontier.top();
        frontier.pop();
        nodes_expanded++;

        std::string state = nodePop->get_state();

        // return Goal state node if nodePop equals the dest string
        if (state == dest)
            return nodePop;
        
        // node has been visited or explored
        explored.push_back(state);        
        
        // Loop through the multimap to see all possible outcomes for nodePop and create a childnode
        for (auto i = data.begin(); i != data.end(); ++i){
            if (i->first == state && !is_explored(explored, i->second.first)){
                Node *child = create_node(*nodePop, i->second.first, i->second.second);
                nodes_generated++;
                frontier.push(child);
            }
        }
        
    }

    return startNode;
}


/*
Name        : reverse
Parameters  : The head of the linked list
Description : Reverse a linkedlist
Returns     : The head of the new linkedlist
*/
Node* reverse(Node* head){
    Node *current_head = head;
    Node *prev = NULL;
    Node *next = NULL;

    while(current_head != NULL){
        next = current_head->get_parent();

        current_head->set_parent(prev);

        prev = current_head;
        current_head = next;
    }

    head = prev;
    return head;
}


int main(int argc, char** argv){
    std::multimap<std::string, std::pair<std::string, float>> data;
    std::map<std::string, float> heuristic;
    int nodes_generated = 0, nodes_expanded = 0;


    // do uninformed search (Uniform Cost Search)
    if (argc == 4){
        read_input_file(argv[1], data);    
        Node *uis = uninformed_search(argv[2], argv[3], data, nodes_generated, nodes_expanded);
    
        std::cout << "nodes_expanded: "     << nodes_expanded       << std::endl;
        std::cout << "nodes_generated: "    << nodes_generated      << std::endl;
        
        // (London to Kassel)
        if (uis->get_state() ==argv[2]){
            std::cout << "distance: infinity" << std::endl;
            std::cout << "route: " << std::endl << "none" << std::endl;
        }else{
            std::cout << "distance: " << uis->get_totalCost() << " km" << std::endl;
            std::cout << "route: " << std::endl;
    
            // Reverse linked list and displa results
            Node *head = reverse(uis);
            while (head->get_parent() != NULL){
                std::cout << head->get_state() << " to ";
                head = head->get_parent();
                std::cout << head->get_state() << ", " << head->get_pathCost() << " km"<< std::endl; 
            }
        }

    }
    

    
    
    // Use for debugging heuristic map
    // int count = 0;
    // std::map<std::string, float>::iterator it;
    // for (auto const &i : heuristic){
    //     count++;
    //     std::cout << count << ") " << i.first << " - " << i.second << std::endl;
    // }
    
    // Use for debugging data multimap
    // int count = 0;
    // for(auto i = data.begin(); i != data.end(); ++i){
    //     count ++;
    //     std::cout << count << ") " << i->first << " -> " << i->second.first << " - " << i->second.second << std::endl;
    // }

    return EXIT_SUCCESS;
}