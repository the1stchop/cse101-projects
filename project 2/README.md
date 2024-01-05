# pa2

## Short Description:
In this assignment we were tasked with implementing Graph ADT, using the List ADT we made last assignment, as well as building a program with it.Here is a list of the files in this directory with a short description about them that made it happen:

-List.c: This file contains the List ADT as well as the constructor, accessor, and manipulator functions for our ADT. These functions will help us make, access, and manipulate Lists in our lex.c.

-Graph.c: This file contains the Graph ADT as well as the constructor, accessor, and manipulator functions for our ADT. These functions will help us make, access, and manipulate Graphs in our FindPath.c.

-FindPath.c: This file houses the main function. It uses the ADTs from List.c and Graph.c to implement an shortest path finder. It takes in an input file that provides the source vertex, edges and destination and will output the shortest path.

-GraphTest.c: This file contains the tests for Graph.c.

-Makefile: This file builds our executable and .o files. It also can format our .c files and clean our directory.

## Build and Clean
To build the Lex executable, type "$make" into the command line. This will create the executable "FindPath" and all the .o files required. Then you should be good to go. To build the ListTest exeutable, type "$make GraphTest". To clear your directory, do "$make clean". This will remove the executable made and all .o files.

