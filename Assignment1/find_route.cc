/*David Chau 1001736889 CSE 4308-002

needs -std=c++11 or better
g++ -o find_route find_route.cc
./find_route input_filename origin_city destination_city


*/
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

class Node
{
    public:
    float distance;
    int level;
    string name, parent;
    
    Node(string name, string parent, float distance, int level)
    {
        this->name=name;
        this->parent=parent;
        this->distance=distance;
        this->level=level;
    }
    
    Node(string name,string parent,float distance)
    {
        this->name=name;
        this->parent=parent;
        this->distance=distance;
    }
};

int main(int argc, char *argv[])
{
    int nodes_generated = 0;
    int nodes_expanded = 0;
    float temp;
    int close=0;
    float low;
    int found=0;
    vector<Node> closed;
    vector<Node> fringe;
    vector<float> sort_fringe;
    vector<Node> input;
    
    ifstream inFile;
    inFile.open(argv[1]);
    
    while(!inFile.eof())
    {
        string intermediate;
        string line;
        float number;
        string location;
        string destination;
        
        getline(inFile,line);
        stringstream delimit(line);
        getline(delimit,intermediate,' ');
        if(intermediate=="END")
        {
            break;
        }
        
        location = intermediate;
        
        getline(delimit,intermediate,' ');
        destination = intermediate;
        
        getline(delimit,intermediate,'\n');
        number = std::stof(intermediate);
        Node a(location,destination,number);
        input.push_back(a);
    }
    inFile.close();
    
    Node root(argv[2],"0",0,0);
    nodes_generated++;
    fringe.push_back(root);
    
    
    if (root.name == argv[3])
    {
        closed.push_back(fringe[0]);
        cout<<"Adding to closed: "<<fringe[0].name<<endl;
        cout<<"nodes expanded: "<<nodes_expanded<<"\nnodes generated: "<<nodes_generated<<"\ndistance: 0 \n route: "<<argv[2]<<endl;
    }
    else
    {
        nodes_expanded++;
        closed.push_back(fringe[0]);
        fringe.erase(fringe.begin());
        for(int i=0;i<input.size();i++)
        {
            if(root.name==input[i].name)
            {
                nodes_generated++;
                Node node(input[i].parent,root.name,input[i].distance,1);
                fringe.push_back(node);
            }
            if(root.name==input[i].parent)
            {
                nodes_generated++;
                Node node(input[i].name,root.name,input[i].distance,1);
                fringe.push_back(node);
            }
            
        }
        if(fringe.size()==0)
        {
            cout<<"nodes expanded: "<<nodes_expanded<<"\nnodes generated: "<<nodes_generated<<"\ndistance: infinity \n route: none"<<endl;
            
        }
        else
        {
            for(int i=0;i<fringe.size();i++)
            {
                temp=fringe[i].distance;
                sort_fringe.push_back(temp);
            }
            sort(sort_fringe.begin(),sort_fringe.end());
            low = sort_fringe[0];
            sort_fringe.erase(sort_fringe.begin());
            while(closed[closed.size()-1].name!=argv[3] && !fringe.empty())
            {
                for(int i=0;i<fringe.size();i++)
                {
                	if(fringe[i].distance == low)
                	{
                		if(fringe[i].name == argv[3])
                		{
                		    nodes_expanded++;
                			closed.push_back(fringe[i]);
                			fringe.erase(fringe.begin()+i);
                			temp = closed.size()-1;
                			found=1;
                		}
                		//close = 0;
                		if(fringe.size()!=0)
                		{
                		    for(int k=0;k<closed.size();k++)//if in closed don't expand
                            {
                                if(fringe[i].name==closed[k].name)
                                {
                                    close=1;
                                    break;
                                }
                                else
                                {
                                    close=0;
                                }
                            }
                		}
                		if(!close  && fringe.size()!=0 && !found)
                		{
                		    nodes_expanded++;
                			closed.push_back(fringe[i]);
                            fringe.erase(fringe.begin()+i);
                            for(int j=0;j<input.size();j++)
                            {
                                //close=0;
                                if(closed[closed.size()-1].name==input[j].name)
                                {
                                    
                                    nodes_generated++;
                                    Node node(input[j].parent,closed[closed.size()-1].name,closed[closed.size()-1].distance+input[j].distance,input[j].level+closed[closed.size()-1].level);
                                    fringe.push_back(node);
                                    
                                }
                                if(closed[closed.size()-1].name==input[j].parent)
                                {
                                    
                                    nodes_generated++;
                                    Node node(input[j].name,closed[closed.size()-1].name,closed[closed.size()-1].distance+input[j].distance,input[j].level+closed[closed.size()-1].level);
                                    fringe.push_back(node);
                                }
                                
                            }
                            
                            if(fringe.size()==0)
                            {
                                cout<<"nodes expanded: "<<nodes_expanded<<"\nnodes generated: "<<nodes_generated<<"\ndistance: 0 \n route: "<<argv[2];
                                break;
                                
                            }
                            else
                            {
                                vector<float> sort_fringe1;
                                for(int k=0;k<fringe.size();k++)
                                {
                                    temp=fringe[k].distance;
                                    sort_fringe1.push_back(temp);
                                }
                                sort(sort_fringe1.begin(),sort_fringe1.end());
                                low = sort_fringe1[0];
                            }
                		}
                		else if(!found)
                		{
                		    nodes_expanded++;
                		    
                			if(fringe.size()==0)
                			{
                			    break;
                			}
                			fringe.erase(fringe.begin()+i);
                			if(fringe.size()!=0)
                			{
                    			vector<float> sort_fringe1;
                    			for(int k=0;k<fringe.size();k++)
                                {
                                    temp=fringe[k].distance;
                                    sort_fringe1.push_back(temp);
                                }
                    		    sort(sort_fringe1.begin(),sort_fringe1.end());
                                low = sort_fringe1[0];
                			}
                		}
                	}
                }
                
            }
            if(found)
            {
                //break;
                cout<<"nodes expanded: "<<nodes_expanded<<"\nnodes generated: "<<nodes_generated<<endl;
                
                vector<string>from;
                vector<string>to;
                vector<float>path;
                float track=0;
                to.insert(to.begin(),closed[closed.size()-1].name);
                from.insert(from.begin(),closed[closed.size()-1].parent);
                
                if(from[0]==argv[2])
                {
                    for(int i=0;i<input.size();i++)
                    {
                        if(from[0]==input[i].name && to[0]==input[i].parent ||
                        from[0]==input[i].parent && to[0]==input[i].name)
                        {
                            track=closed[closed.size()-1].distance-input[i].distance;
                            path.insert(path.begin(),input[i].distance);
                            break;
                        }
                        
                    }
                }
                while(from[0]!=argv[2])
                {
                    for(int i=0;i<input.size();i++)
                    {
                        if(from[0]==input[i].name && to[0]==input[i].parent ||
                        from[0]==input[i].parent && to[0]==input[i].name)
                        {
                            if(track==0)
                            {
                                track=closed[closed.size()-1].distance-input[i].distance;
                            }
                            else
                            {
                                track-=input[i].distance;
                            }
                            
                            path.insert(path.begin(),input[i].distance);
                            break;
                        }
                        
                    }
                    for(int i=0;i<closed.size();i++)
                    {
                        if(track==closed[i].distance)
                        {
                            track=closed[i].distance;
                            to.insert(to.begin(),closed[i].name);
                            from.insert(from.begin(),closed[i].parent);
                            break;
                        }
                    }
                    if(from[0]==argv[2])
                    {
                        for(int i=0;i<input.size();i++)
                        {
                            if(from[0]==input[i].name && to[0]==input[i].parent ||
                            from[0]==input[i].parent && to[0]==input[i].name)
                            {
                                path.insert(path.begin(),input[i].distance);
                                break;
                            }
                            
                        }
                    }
                    
                }
                
                for(int i=0;i<from.size();i++)
                {
                    cout<<setprecision(1)<<fixed;
                    cout<<from[i]<<" to "<<to[i]<<", "<<path[i]<<" km"<<endl;
                }
            }
            else
            {
                cout<<"nodes expanded: "<<nodes_expanded<<"\nnodes generated: "<<nodes_generated<<"\ndistance: infinity\nroute: none"<<endl;
            }
        }
        
    }
    
    return 0;
}
