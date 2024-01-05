# pa5

## Short Description:
In this assignment we were tasked with implementing a new List ADT as well as building a program with it.Here is a list of the files in this directory with a short description about them that made it happen:

-List.c: This file contains the List ADT as well as the constructor, accessor, and manipulator functions for our ADT. These functions will help us make, access, and manipulate Lists in our Shuffle.c.

-Shuffle.c: This file houses the main function. It uses the List ADT from List.c to find the number of shuffles it takes for a list to be brought back to its original order. It takes in an number that will be the size of the deck that will be shuffled and outputs the number of shuffles from size 1 all the way to input.

-ListTest.c: This file contains the tests for Test.c

-List.h: This is the header file for List.c.

-Makefile: This file builds our executable and .o files. It also can format our .c files and clean our directory.


## Build and Clean
To build the Shuffle executable, type "$make" into the command line. This will create the executable "Shuffle" and all the .o files required. Then you should be good to go. To build the ListTest executable, type "$make ListTest". To clear your directory, do "$make clean". This will remove the executable made and all .o files. Running "$make format" formats all .c files in the directory.