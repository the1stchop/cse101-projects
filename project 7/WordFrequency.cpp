//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa8
//-----------------------------------------------------------------------------
// WordFrequency.cpp
// Implementation file for WordFrequency
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include<fstream>
#include<algorithm>
#include"Dictionary.h"

using namespace std;

int main(int argc, char *argv[]){

    // check command line for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    int line_count;
    size_t begin, end, len;
    ifstream infile;
    ofstream outfile;
    string line;
    string token;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#%$^&*()-_=+0123456789";

    // opening infile and outfile
    infile.open(argv[1]);
    outfile.open(argv[2]);

    // making Dictionary
    Dictionary dict;

    line_count = 0;
    // read each line of input file, then count and print tokens 
    line_count = 0;
    while( getline(infile, line) )  {
        line_count++;
        len = line.length();

        // get first token
        begin = min(line.find_first_not_of(delim, 0), len);
        end = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end-begin);
      
        while( token!="" ){  // we have a token

            // convert token to all lower. got the idea to use the transform function from
            // geeksforgeeks. https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/#
            transform(token.begin(), token.end(), token.begin(), ::tolower);
            
            // filling the dictionary
            if(dict.contains(token)){
                dict.setValue(token, dict.getValue(token) + 1);
            }
            else{
                dict.setValue(token, 1);
            }

            // get next token
            begin = min(line.find_first_not_of(delim, end+1), len);
            end   = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);
        }
    }

    // print to outfile
    outfile << dict << endl;

    // closing files
    infile.close();
    outfile.close();

}