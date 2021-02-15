# Artficial-Intelligence

**Assignment 1** is implementing a state space search algorithm that can a find a route between any two cities. The program will be called find_route, and will take exactly commandline aruments as follows:

  ./find_route input1.txt Bremen Kassel (For doing Uninformed Search)
  
  or 
  
  ./find_route input1.txt Bremen Kassel h_kassel.txt (For doing Informed Search)

Argument input_filename is the name of a text file such as input1.txt, that describes road connections between cities in some part of the world. For example, the road system described by file input1.txt can be visualized with the photo below:

<img src="photo.gif" title="Visualized Photo"/>


The last line contains the items "END OF INPUT" and that is how the program can detect that it has reached the end of the file. The other lines of the file contain, in this order, a source city, destination city, and the length in kilometers of the road connecting directly those two cities. Each name will be a single word


## Compilation Instruction and Programming Language 

The programming language used is C++.


  #### Uninformed Search 
    g++ -c find_route.cpp -o find_route
    ./find_route input1.txt Bremen Kassel

  #### Informed Search
    g++ -c find_route.cpp -o find_route
    ./find_route input1.txt Bremen Kassel h_kassel.txt
  
  
