//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa8
//-----------------------------------------------------------------------------
// Order.cpp
// Implementation file for Order
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include<fstream>
#include"Dictionary.h"

using namespace std;

int main(int argc, char *argv[]){

    // check command line for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // opening in and out files
    ifstream infile;
    infile.open(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);

    // make dictionary
    Dictionary dict;

    // filling the dictionary
    string line;
    int counter = 1;
    while(getline(infile, line)){
        dict.setValue(line, counter);
        counter += 1;
    }

    // printing the stuff
    outfile << dict << endl;
    outfile << dict.pre_string() << endl;

    // closing files
    infile.close();
    outfile.close();

    return 0;
}