# pa1

## Short Description:
In this assignment we were tasked with implementing List ADT, using a doubly linked list, as well as building a program with it.Here is a list of the files in this directory with a short description about them that made it happen:

-List.c: This file contains our List ADT as well as the constructor, accessor, and manipulator functions for our ADT. These functions will help us make, access, and manipulate Lists in our lex.c.

-Lex.c: This file houses the main function. It uses the ADT from List.c to implement an array sorter. It takes in a list and will output a new, sorted list.

-ListTest.c: This file contains the tests for List.c.

-Makefile: This file builds our executable and .o files. It also can format our .c files and clean our directory.

## Build and Clean
To build the Lex executable, type "$make" into the command line. This will create the executable "Lex" and all the .o files required. Then you should be good to go. To build the ListTest exeutable, type "$make ListTest". To clear your directory, do "$make clean". This will remove the execuable made and all .o files.

