//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa8
//-----------------------------------------------------------------------------
// Dictionary.cpp
// Implementation file for Dictionary ADT
//-----------------------------------------------------------------------------
#include<sstream>
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

#define RED 1
#define BLACK 0

// Private Constructor --------------------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = BLACK;
}

// Class Constructors & Destructors -------------------------------------------

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
    nil = new Node(":3",0);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    nil = new Node(":3", 0);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
    postOrderDelete(root);
    delete nil;
}


// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R != nil){
        inOrderString(s, R->left);
        s += R->key;
        s += " : ";
        s += std::to_string(R->val);
        s += "\n";
        inOrderString(s,R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R != nil){
        s += R->key;
        if(R->color == RED){
            s += " (RED)";
        }
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s,R->right);
    }
}

void Dictionary::BST_insert(Node* M){
    Node* P = nil;
    Node* R = root;
    while(R != nil){
        P = R;
        if(M->key < R->key){
            R = R->left;
        }
        else if(M->key > R->key){
            R = R->right;
        }
        else{
            R->val = M->val;
            return;
        }
    }

    Node* N = new Node(M->key, M->val);
    if(P == nil){
        N->parent = nil;
        N->left = nil;
        N->right = nil;
        root = N;
    }
    else if(M->key < P->key){
        P->left = N;
        N->parent = P;
        N->left = nil;
        N->right = nil;
    }
    else{
        P->right = N;
        N->parent = P;
        N->left = nil;
        N->right = nil;
    }
    num_pairs += 1;
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if(R != N){
        BST_insert(R);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
    if(R != nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if(R == nil || k == R->key){
        return R;
    }
    else if(k < R->key){
        return search(R->left, k);
    }
    else{
        return search(R->right, k);
    }
    return nil;
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    Node* temp = R;
    if (temp != nil){
        while(temp->left != nil){
            temp = temp->left;
        }
    }
    return temp;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    Node* temp = R;
    if (temp != nil){
        while(temp->right != nil){
        temp = temp->right;
        }
    }
    return temp;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    if(N == nil){
        return nil;
    }
    else if(N->right != nil){
        return findMin(N->right);
    }
    else{
        Node* temp = N;
        Node* y = N->parent;
        while(y != nil && temp == y->right){
            temp = y;
            y = y->parent;
        }
        return y;
    }
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    if(N == nil){
        return nil;
    }
    else if(N->left != nil){
        return findMax(N->left);
    }
    else{
        Node* temp = N;
        Node* y = N->parent;
        while(y != nil && temp == y->left){
            temp = y;
            y = y->parent;
        }
        return y;
    }
}

// Transplant()
// remove helper function
void Dictionary::transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    if(v != nil){
        v->parent = u->parent;
    }

}

// RBT Helper Functions (Optional) -----------------------------------------
   
// LeftRotate()
void Dictionary::LeftRotate(Node* N){
    // set x and y
    Node* x = N;
    Node* y = N->right;

    // turn y's left subtree into x.s right subtree
    x->right = y->left;
    // prolly not necessary cause using sent node
    if(y->left != nil){
        y->left->parent = x;
    }

    // link y's parent to x
    y->parent = x->parent;
    if(x->parent == nil){
        root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }

    // put x on y's right
    y->left = x;
    x->parent = y;

}

// RightRotate()
void Dictionary::RightRotate(Node* N){
    // set x and y
    Node* x = N;
    Node* y = N->left;

    // turn y's right subtree into x's left subtree
    x->left = y->right;
    // prolly not necessary cause using sent node
    if(y->right != nil){
        y->right->parent = x;
    }

    // link y's parent to x
    y->parent = x->parent;
    if(x->parent == nil){
        root = y;
    }
    else if(x == x->parent->right){
        x->parent->right = y;
    }
    else{
        x->parent->left = y;
    }

    // put x on y's right
    y->right = x;
    x->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
    Node* z = N;
    Node* y;

    while(z->parent->color == RED){
        if(z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if(y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->right){
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RightRotate(z->parent->parent);
            }
        }
        else{
            y = z->parent->parent->left;
            if(y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->left){
                    z = z->parent;
                    RightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LeftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;   
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
    Node* x = N;
    Node* w;
    while(x != root && x->color == BLACK){
        if(x == x->parent->left){
            w = x->parent->right;
            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            }
            else{
                if(w->right->color == BLACK){
                    w->right->color = BLACK;
                    w->color = RED;
                    RightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(x->parent);
                x = root;
            }
        }
        else{
            w = x->parent->left;
            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                RightRotate(x->parent);
                w = x->parent->left;
            }
            if(w->right->color == BLACK && w->left->color == BLACK){
                w->color = RED;
                x = x->parent;
            }
            else{
                if(w->left->color == BLACK){
                    w->right->color = BLACK;
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
    Node* z = N;
    Node* y = N;
    Node* x;
    
    int y_original_color = y->color;

    if(z->left == nil){
        x = z->right;
        RB_Transplant(z, z->right);
    }
    else if(z->right == nil){
        x = z->left;
        RB_Transplant(z, z->left);
    }
    else{
        y = findMin(z->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent == z){
            x->parent = y;
        }   
        else{
            RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if(y_original_color == BLACK){
        RB_DeleteFixUp(x);
    }
}

// Access functions ----------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    if(search(root,k) == nil){
        return false;
    }
    else{
        return true;
    }
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    Node* temp = search(root,k);
    if(temp == nil){
        throw std::logic_error("getValue: key does not exist");
    }
    return temp->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    if(current != nil){
        return true;
    }
    else{
        return false;
    }
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if(hasCurrent()){
        return current->key;
    }
    else{
        throw std::logic_error("currentKey(): current iterator not defined");
    }
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if(hasCurrent()){
        return current->val;
    }
    else{
        throw std::logic_error("currentVal(): current iterator not defined");
    }
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    Node* P = nil;
    Node* R = root;
    while(R != nil){
        P = R;
        if(k < R->key){
            R = R->left;
        }
        else if(k > R->key){
            R = R->right;
        }
        else{
            R->val = v;
            return;
        }
    }

    Node* N = new Node(k, v);
    if(P == nil){
        N->parent = nil;
        N->left = nil;
        N->right = nil;
        root = N;
    }
    else if(k < P->key){
        P->left = N;
        N->parent = P;
        N->left = nil;
        N->right = nil;
    }
    else{
        P->right = N;
        N->parent = P;
        N->left = nil;
        N->right = nil;
    }
    N->color = RED;
    RB_InsertFixUp(N);
    num_pairs += 1;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    Node* N = search(root,k);

    if(N == nil){
        throw std::logic_error("remove(): key does not exist");
    }

    if(current == N){
        current = nil;
    }

    RB_Delete(N);
    num_pairs -= 1;
    delete N;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    if(root != nil){
        current = findMin(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    if(root != nil){
        current = findMax(root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if(hasCurrent()){
        current = findNext(current);
    }
    else{
        throw std::logic_error("next(): current iterator not defined");
    }
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if(hasCurrent()){
        current = findPrev(current);
    }
    else{
        throw std::logic_error("prev(): current iterator not defined");
    }
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string s;
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string s;
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    if(to_string() == D.to_string()){
        return true;
    }
    else{
        return false;
    }
}

// Overloaded Operators ----------------------------------------------------
   
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    if(this != &D){
        Dictionary temp = D;

        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }

    return *this;
}
