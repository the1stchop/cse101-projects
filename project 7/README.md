# pa8

## Short Description:
In this assignment we are tasked with edited the Dictionary ADT we built last assignment to implement a Red-Black tree ADT. We will then use it to create a word frequency program. Our order program from last assignment is also here. Here is a list of the files in this directory with a short description about them that made it happen:

-Dictionary.cpp: This file contains the Dictionary ADT as well as the constructor, accessor, and manipulator functions for our ADT. These functions will help us make, access, and manipulate Dictionaries in our WordFrequency.cpp and Order.cpp.

-WordFrequency.cpp: This file contains the main function for WordFrequency. It uses the ADT from Dictionary.cpp to use the Dctionary functions on dictionaries. It takes in a .txt file and outputs the frequencies of all the words in it in alphabetical order. To make the all the words lowercase, I used the function transform. got the idea from geeksforgeeks. https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/#

-Order.cpp: This file houses the main function. It uses the ADT from Dictionary.cpp to use Dictionary functions on dictionaries. It takes in an input file that provides the words that will be put into a dictionary and will output them in two representations. The first way will put the words in alphabetical order with their values. The second way will place the words in the order obtained from a pre-order tree walk.

-DictionaryTest.cpp: This file contains the tests for Dictionary.cpp.

-Dictionary.h: This is the header file for Dictionary.cpp.

-Makefile: This file builds our executable and .o files. It also can format our .cpp files and clean our directory.


## Build and Clean
To build the Order executable, type "$make WordFrequency" into the command line. This will create the executable "WordFrequency" and all the .o files required. To build the Order executable, type "$make Order" into the command line. This will create the executable "Order" and all the .o files required Then you should be good to go. To build the DictionaryTest executable, type "$make Dictionary Test". To clear your directory, do "$make clean". This will remove the executable made and all .o files. Running "$make format" formats all .c files in the directory.