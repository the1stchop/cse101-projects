//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa5
//-----------------------------------------------------------------------------
// BigIntegerTest.cpp
// Test file for BigInteger
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){
    string x = "20";
    BigInteger A = BigInteger("111122223333");
    BigInteger B = BigInteger("111122223333");
    BigInteger C = BigInteger("-333333333333");
    if(A == B){
        cout << "coder-chan you did it! :3" << endl;
    }
    if(A <= B){
        cout << "coder-chan you did it! :D" << endl;
    }
    if(A >= B){
        cout << "coder-chan you did it! :/" << endl;
    }
    if(A > C){
        cout << "what is the jiggle jiggle skin?" << endl;
    }
    BigInteger D = A + B;
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "C = " << C << endl;
    cout << "D = " << D << endl;
    cout << "A * B = " << A * B << endl;
    cout << "A + C = " << A + C << endl;
    cout << "A - C = " << A - C << endl;
    cout << "A - B = " << A - B << endl;
    cout << "C - A = " << C - A << endl;
    cout << "B * C = " << B * C << endl;
    return 1;
}