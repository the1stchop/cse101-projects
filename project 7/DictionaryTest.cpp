//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa8
//-----------------------------------------------------------------------------
// DictionaryTest.cpp
// A test for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){
   string s;
   string S[] =   {
                     "plaices",
                     "ambusher",
                     "crosby",
                     "wattles",
                     "pardoner",
                     "pythons",
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",
                     "dissocialised",
                     "cohabit",
                     "hemiolia",
                     "cantling",
                     "glamorized",
                     "millesimal",
                     "glagolitic"
                  };

   Dictionary A;
   Dictionary B;

   if(A == B){
    cout << "True" << endl;
   }
   else{
    cout << "False" << endl;
   }

   // insert some pairs into A
   for(int i=0; i<26; i++){
      A.setValue(S[i], i+1);
   }

   // check all stuff in Dictionary A
   cout << "Dict A size: " << A.size() << endl;
   cout << "Dict A stuff: " << endl << A << endl;

   // copy A to B
   B = A;

   // adding some values of a
   A.setValue("haii", 100);
   A.setValue(":3", 101);
   A.setValue(":/",102);

   // checking A and B
   cout << "Dict A size: " << A.size() << endl;
   cout << "Dict A stuff: " << endl << A << endl;

   cout << "Dict B size: " << B.size() << endl;
   cout << "Dict B stuff: " << endl << B << endl;

   // removing stuff from A
   A.remove("haii");
   A.remove(":3");
   A.remove(":/");

   // check A is same as B
   if(A == B){
    cout << "True" << endl;
   }
   else{
    cout << "False" << endl;
   }

   return 0;
}