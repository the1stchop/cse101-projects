//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa5
//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
    int i, n=10;
    List A;
    List B;
    List D;
    List E;

    for(i=1; i<=n; i++){
       A.insertAfter(i);
    }

    cout << endl;
    cout << "A = " << A << endl;
    cout << endl;
    cout << "A length = " << A.length() << endl;
    cout << "A position = " << A.position() << endl;

    D.insertAfter(1);
    D.insertAfter(2);
    D.insertAfter(3);
    B.insertAfter(4);
    B.insertAfter(5);
    B.insertAfter(6);

    List C;
    C = D.concat(B);

    E = A;

    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "E = " << E << endl;
    cout << endl;
    cout << "C = " << C << endl;
    cout << "C length = " << C.length() << endl;
    cout << "C position = " << C.position() << endl;
    cout << endl;

    List G;
    G.insertBefore(34);
    G.insertBefore(77);
    G.insertBefore(77);
    G.insertBefore(1);
    G.insertBefore(34);
    G.insertBefore(1);
    G.insertBefore(55);
    G.insertBefore(77);
    cout << "G.FindPrev(99) = " << G.findPrev(99) << endl;

}