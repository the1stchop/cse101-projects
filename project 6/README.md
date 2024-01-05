# pa6

## Short Description:
In this assignment we were tasked with implementing a new big integer ADT as well as building a program with it.Here is a list of the files in this directory with a short description about them that made it happen:

-List.cpp: This file contains the List ADT as well as the constructor, accessor, and manipulator functions for our ADT. These functions will help us make, access, and manipulate Lists.

-BigInteger.cpp: This file contains the BigInteger ADT as well as teh constructor, accessor, and manipulator function for our ADT. these functions will help us make, access, and manipulate BigIntegers in our Arithmetic.cpp. It uses the List ADT in List.cpp.

-Arithmetic.c: This file houses the main function. It uses the BigInteger ADT from BigInteger.cpp List ADT from List.cpp to do several arithmetic operations on the given input.

-ListTest.cpp: This file contains the tests for Test.c

-BigInteger.cpp: This file contains the tests for BigInteger.cpp.

-List.h: This is the header file for List.c.

-BigInteger.h: This is the header file of BigInteger.cpp/

-Makefile: This file builds our executable and .o files. It also can format our .c files and clean our directory.


## Build and Clean
To build the Arithmetic executable, type "$make" into the command line. This will create the executable "Arithmetic" and all the .o files required. Then you should be good to go. To build the ListTest executable, type "$make ListTest". To build the BigIntegerTest executable, type "$make BigIntegerTest". To clear your directory, do "$make clean". This will remove the executable made and all .o files. Running "$make format" formats all .c files in the directory.