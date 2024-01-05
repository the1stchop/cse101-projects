//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa6
//-----------------------------------------------------------------------------
// BigInteger.cpp
// Implementation file for BigInteger ADT
//-----------------------------------------------------------------------------
#include<sstream>
#include<stdexcept>
#include<iomanip>
#include"BigInteger.h"

const ListElement base = 1000000000;
const int power = 9;

// Class Constructors & Destructors -------------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    signum = 0;
    digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
    if(x > 0){
        signum = 1;
    }
    else if(x < 0){
        signum = -1;
        x *= -1;
    }
    else{
        signum = 0;
    }

    digits = List();
    long remainder;
    while(x > 0){
        remainder = x % base;
        digits.insertAfter(remainder);
        x /= base;
    }
}

BigInteger::BigInteger(std::string s){
    int string_Length = s.length();

    if(string_Length == 0){
        // raise error
    }

    // get preliminary signum
    if(s[0] == '-'){
        signum = -1;
        s.erase(0,1);
        string_Length -= 1;
    }
    else if(s[0] == '+'){
        signum = 1;
        s.erase(0,1);
        string_Length -= 1;

    }
    else{
        signum = 1;
    }
    
    // elminate leading zeroes
    while(string_Length > 1 && s[0] == '0'){
        s.erase(0,1);
        string_Length -= 1;
    }

    // if only 0
    if(s[0] == '0'){
        signum = 0;
    }

    // if string is empty
    if(string_Length == 0){
        throw std::length_error("BigInteger: BigInteger(std::string x): string is empty");
    }

    // check for non-numeric characters
    for(int i = 0; i < string_Length; i++){
        if(!isdigit(s[i])){
            throw std::invalid_argument("BigInteger: BigInteger(std::string x): non-numeric characters in string");
        }
    }

    // string -> List
    digits = List();
    std::string element;
    if(s[0] != '0'){
        while(string_Length > power){
            element = s.substr(string_Length - power, power);
            digits.insertAfter(stol(element));
            string_Length -= power;
        }
        if(string_Length > 0){
            element = s.substr(0, string_Length);
            digits.insertAfter(stol(element));
        }

    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    signum = N.signum;
    digits = N.digits;
}

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    List A = digits;
    List B = N.digits;

    // checking for signs
    if(signum > N.signum){
        return 1;
    }

    if(signum < N.signum){
        return -1;
    }

    A.moveFront();
    B.moveFront();
    long x, y;
    while(A.position() < A.length()){
        x = A.moveNext();
        y = B.moveNext();

        if(x > y){
            return 1;
        }

        if(x < y){
            return -1;
        }
    }
    return 0;
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    if(signum != 0){
        signum *= -1;
    }
}

// BigInteger Helper operations --------------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
    L.moveFront();
    while(L.position() < L.length()){
        L.moveNext();
        L.setBefore(L.peekPrev() * -1);
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
    ListElement a, b;
    S.clear();
    A.moveBack();
    B.moveBack();

    while(A.position() > 0 && B.position() > 0){
        a = A.movePrev();
        b = B.movePrev();
        S.insertAfter(a + sgn*b);
    }

    while(A.position() > 0){
        a = A.movePrev();
        S.insertAfter(a);
    }

    while(B.position() > 0){
        b = B.movePrev();
        S.insertAfter(sgn*b);
    }
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){
    int sign;
    ListElement q, r, num, carry;
    carry = 0;

    // cheacking if MSD is negative
    L.moveFront();
    if(L.peekNext() < 0){
        negateList(L);
        normalizeList(L);
        return -1;
    }

    // loop from LSD
    L.moveBack();
    while(L.position() > 0){
        num = L.movePrev();
        num += carry;
        q = num / base;
        r = num % base;

        if(r < 0){
        num = r + base;
        carry = q - 1;
        }
        else{
        num = r;
        carry = q;
        }

        L.setAfter(num);
    }

    if(carry != 0){
        L.moveFront();
        L.insertBefore(carry);
    }

    // removing leading zeros
    L.moveFront();
    while(L.length() > 0 && L.peekNext() == 0){
        L.eraseAfter();
    }

    // calculating sign
    if(L.length() == 0){
        sign = 0;
    }
    else if(L.peekNext() > 0){
        sign = 1;
    }
    else{
        sign = -1;
        negateList(L);
        normalizeList(L);
    }

    return sign;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
    L.moveBack();
    for(int i = 0; i < p; i++){
        L.insertBefore(0);
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
    if(m != 1){
        ListElement x;
        L.moveFront();
        while(L.position() < L.length()){
            x = L.moveNext();
            if(x != 0){
                L.setBefore(x * m);
            }
        }
    }
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger sum;

    List A = digits;
    List B = N.digits;
    List& S = sum.digits;

    if(signum == N.signum){
        sumList(S, A, B, 1);
        normalizeList(S);
        sum.signum = signum;
    }
    else{
        sumList(S, A, B, -1);
        sum.signum = normalizeList(S) * signum;
    }

    return sum;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger B = N;
    B.negate();
    return add(B);
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger product;
    List scalarMult;
    List A = digits;
    List B = N.digits;
    ListElement b;

    B.moveBack();
    for(int i = 0; i < B.length(); i ++){
        scalarMult.clear();
        b = B.movePrev();
        scalarMult = A;
        scalarMultList(scalarMult, b);
        shiftList(scalarMult, i);
        sumList(product.digits, scalarMult, product.digits, 1);
        normalizeList(scalarMult);
    }
    
    if(signum == N.sign()){
        product.signum = 1;
    }
    else{
        product.signum = -1;
    }
    return product;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    std::string s;
    if(signum == -1){
        s.append("-");
    }
    if(signum == 0){
        s.append("0");
    }
    else{
        digits.moveFront();
        while(digits.position()<digits.length()){
            std::ostringstream ss;
            ss << std::setw(power) << std::setfill('0') << digits.moveNext();
            s.append(ss.str());
        }
    }
    return s;
}

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();

}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 0){
        return true;
    }
    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == -1){
        return true;
    }
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 1){
        return false;
    }
    return true;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 1){
        return true;
    }
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == -1){
        return false;
    }
    return true;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A;
}
