//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa6
//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"


// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state.
List::List(){
    frontDummy = new Node(-420);
    backDummy = new Node(-15);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
}

// Copy Constructor.
List::List(const List& L){
    // make this an empty List
    frontDummy = new Node(-420);
    backDummy = new Node(-15);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    
    // load elements of this L into this List
    Node* N = L.frontDummy->next;
    while (N != L.backDummy){
        this->insertBefore(N->data);
        N = N->next;
    }
}

// Destructor
List::~List(){
    moveFront();
    while(num_elements != 0){
        eraseAfter();
    }
    delete(frontDummy);
    delete(backDummy);
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return(num_elements);    
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    if(num_elements <= 0){
        throw std::length_error("List: front(): tried getting elements from empty List");
    }

    return(frontDummy->next->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if(num_elements <= 0){
        throw std::length_error("List: back(): tried getting elements from empty List");
    }

    return(backDummy->prev->data);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return(pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    if(pos_cursor >= num_elements){
        throw std::range_error("List: peekNext(): tried accessing backDummy");
    }

    return(afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if(pos_cursor <= 0){
        throw std::range_error("List: peekPrev(): tried accessing frontDummy");
    }

    return(beforeCursor->data);
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    moveFront();
    while(num_elements != 0){
        eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
    if(pos_cursor >= num_elements){
        throw std::range_error("List: moveNext(): already at back of List");
    }

    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor += 1;
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if(pos_cursor <= 0){
        throw std::range_error("List: movePrev(): already at front of List");
    }

    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor -= 1;
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    Node* N = new Node(x);

    N->prev = beforeCursor;
    N->next = afterCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;

    num_elements += 1;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    Node* N = new Node(x);

    N->prev = beforeCursor;
    N->next = afterCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;

    num_elements += 1;
    pos_cursor += 1;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if(pos_cursor >= num_elements){
        throw std::range_error("List: setafter(): tried overwriting backDummy");
    }

    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if(pos_cursor <= 0){
        throw std::range_error("List: setBefore(): tried overwriting frontDummy");
    }

    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    if(pos_cursor >= num_elements){
        throw std::range_error("List: eraseAfter(): tried erasing while at back of List");
    }

    Node* N = afterCursor;

    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;

    num_elements -= 1;
    delete N;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if(pos_cursor <= 0){
        throw std::range_error("List: eraseBefore(): tried erasing while at front of List");
    }

    Node* N = beforeCursor;

    beforeCursor = beforeCursor->prev;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;

    num_elements -= 1;
    pos_cursor -= 1;
    delete N;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
    while(pos_cursor < num_elements){
        if(peekNext() == x){
            moveNext();
            return pos_cursor;
        }
        moveNext();
    }
    pos_cursor = num_elements;
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    while(pos_cursor > 0){
        if(peekPrev() == x){
            movePrev();
            return pos_cursor;
        }
        movePrev();
    }
    pos_cursor = 0;
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    Node* current = frontDummy->next;
    Node* temp;
    Node* duplicate;
    while(current != backDummy){
        temp = current;
        while(temp != backDummy){
            if(temp->next->data == current->data){
                duplicate = temp->next;
                temp->next = temp->next->next;
                temp->next->prev = temp;
                delete duplicate;
                num_elements -= 1;
            }
            else{
            temp = temp->next;
            }
        }
        current = current->next;
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List C;
    Node* N = this->frontDummy->next;
    Node* M = L.frontDummy->next;
    while( N!=backDummy){
       C.insertBefore(N->data);
       N = N->next;
    }
    while( M!=L.backDummy){
       C.insertBefore(M->data);
       M = M->next;
    }
    C.pos_cursor = 0;
    C.beforeCursor = C.frontDummy;
    C.afterCursor = C.frontDummy->next;
    return C;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    Node* N = nullptr;
    std::string s = "";

    for(N=frontDummy->next; N!=backDummy; N=N->next){
       s += std::to_string(N->data)+" ";
    }
   
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;
 
    eq = ( this->num_elements == R.num_elements);
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    while( eq && N!=backDummy){
       eq = (N->data==M->data);
       N = N->next;
       M = M->next;
    }
    return eq;
}

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();

}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if( this != &L ){ // not self assignment
      // make a copy of L
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(num_elements, temp.num_elements);
      std::swap(pos_cursor, temp.pos_cursor);
   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return

}