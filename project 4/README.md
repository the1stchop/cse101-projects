# pa4

## Short Description:
In this assignment we were tasked with implementing a Matrix ATP, using a modified List ADT and from the last assignments, as well as building a program with it.Here is a list of the files in this directory with a short description about them that made it happen:

-List.c: This file contains the List ADT as well as the constructor, accessor, and manipulator functions for our ADT. These functions will help us make, access, and manipulate Lists in our lex.c.

-Matrix.c: This file contains the Matrix ADT as well as the constructor, accessor, and manipulator functions for our ADT. These functions will help us make, access, and manipulate Matrices in our Sparse.c.

-Sparse.c: This file houses the main function. It uses the ADTs from List.c and Matrix.c to use arithmetic on Matrices. It takes in an input file that provides the size and non-zero entries of Matrices A and B and will output the the required Matrices.

-MatrixTest.c: This file contains the tests for Matrix.c.

-ListTest.c: This file contains the tests for Test.c

-Matrix.h: This is the header file for Matrix.c.

-List.h: This is the header file for List.c.

-Makefile: This file builds our executable and .o files. It also can format our .c files and clean our directory.


## Build and Clean
To build the Sparse executable, type "$make" into the command line. This will create the executable "Sparse" and all the .o files required. Then you should be good to go. To build the MatrixTest executable, type "$make MatrixTest". To clear your directory, do "$make clean". This will remove the executable made and all .o files. Running "$make format" formats all .c files in the directory.