# pa3

## Short Description:
In this assignment we were tasked with implementing Depth First Searh, using the List ADT and Graph ADT from the last assignments, as well as building a program with it.Here is a list of the files in this directory with a short description about them that made it happen:

-List.c: This file contains the List ADT as well as the constructor, accessor, and manipulator functions for our ADT. These functions will help us make, access, and manipulate Lists in our lex.c.

-Graph.c: This file contains the Graph ADT as well as the constructor, accessor, and manipulator functions for our ADT. These functions will help us make, access, and manipulate Graphs in our FindComponents.c.

-FindComponents.c: This file houses the main function. It uses the ADTs from List.c and Graph.c to implement a strongly connected components finder. It takes in an input file that provides the edges and and number of verticies of a graph and will output the an adjacency list and stronly connected components of the graph.

-GraphTest.c: This file contains the tests for Graph.c.

-Graph.h: This is the header file for Graph.c.

-List.h: This is the header file for List.c.

-Makefile: This file builds our executable and .o files. It also can format our .c files and clean our directory.


## Build and Clean
To build the FindComponents executable, type "$make" into the command line. This will create the executable "FindComponents" and all the .o files required. Then you should be good to go. To build the ListTest exeutable, type "$make GraphTest". To clear your directory, do "$make clean". This will remove the executable made and all .o files.