//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa5
//-----------------------------------------------------------------------------
// Shuffle.cpp
// Implementation fil for Shuffle
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

void shuffle(List& D){
    // if List is 1
    if(D.length() == 1){
        return;
    }

    List A;
    int split = D.length() / 2;

    // left split
    D.moveFront();
    for(int i = 0;i<split;i++){
        A.insertBefore(D.peekNext());
        D.moveNext();
        D.eraseBefore();
    }

    // shuffling A to right side;
    A.moveFront();
    while(A.position() != A.length()){
        D.moveNext();
        D.insertBefore(A.peekNext());
        A.moveNext();
    }
}

int main(int argc, char *argv[]){

    // check command line for correct number of arguments
    if (argc != 2) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // grabbing input
    int deck = atoi(argv[1]);

    // printing title shit
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;

    List A, temp;
    int counter = 0;
    for(int i = 1; i <= deck; i++){

        for(int j = 1; j <= i; j++){
            A.insertAfter(j);
        }

        temp = A;
        shuffle(temp);
        counter += 1;

        while(!(temp == A)){
            shuffle(temp);
            counter += 1;
        }

        // print out deck number and number of shuffles
        cout << i << "               " << counter << endl;

        //reset Lists and counter
        A.clear();
        temp.clear();
        counter = 0;

    }
    
}