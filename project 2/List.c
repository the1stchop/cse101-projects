//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa2
//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include "List.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj *Node;

// private NodeObj type
typedef struct NodeObj {
  int data;
  Node prev;
  Node next;
} NodeObj;

typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// Creates and returns a new Node
Node newNode(int data) {
  Node N = malloc(sizeof(NodeObj));
  assert(N != NULL);
  N->data = data;
  N->next = NULL;
  N->prev = NULL;
  return (N);
}

// Frees all heap memory pointed to by *pN, set *pN to NULL.
void freeNode(Node *pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}

// Creates and returns a new empty List.
List newList(void) {
  List L;
  L = malloc(sizeof(ListObj));
  assert(L != NULL);
  L->front = L->back = L->cursor = NULL;
  L->length = 0;
  L->index = -1;
  return (L);
}

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List *pL) {
  if (pL != NULL && *pL != NULL) {
    clear(*pL);
  }
  free(*pL);
  *pL = NULL;
}

// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
int length(List L) {
  // the case that we calling on NULL List reference
  if (L == NULL) {
    printf("List Error: calling length() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
  if (L == NULL) {
    printf("List Error: calling index() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  return L->index;
}

// Returns front element of L. Pre: length()>0
int front(List L) {
  if (L == NULL) {
    printf("List Error: calling front() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return L->front->data;
}

// Returns back element of L. Pre: length()>0
int back(List L) {
  if (L == NULL) {
    printf("List Error: calling front() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return L->back->data;
}

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
  if (L == NULL) {
    printf("List Error: calling get() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (length(L) == 0 && index(L) < 0) {
    printf("List Error: get() pre-conditions not met\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == NULL) {
    printf("List Error: calling get() on NULL cursor\n");
    exit(EXIT_FAILURE);
  }
  return L->cursor->data;
}

// Returns true iff Lists A and B are in same state, and returns false
// otherwise.
bool equals(List A, List B) {
  if (A == NULL || B == NULL) {
    printf("List Error: calling equals() on NULL list reference\n");
    exit(EXIT_FAILURE);
  }

  bool eq;
  Node N, M;

  eq = (length(A) == length(B));
  N = A->front;
  M = B->front;
  while (eq && N != NULL) {
    eq = (N->data == M->data);
    N = N->next;
    M = M->next;
  }
  return eq;
}

// Returns true if Q is empty, otherwise returns false.
bool isEmpty(List L) {
  if (L == NULL) {
    printf("List Error: calling isEmpty() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return (L->length == 0);
}
// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L) {
  if (L == NULL) {
    printf("List Error: calling clear() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  while (!isEmpty(L)) {
    deleteFront(L);
  }
  L->cursor = NULL;
  L->index = -1;
}

// Overwrites the cursor element’s data with x. Pre: length() > 0, index() >= 0
void set(List L, int x) {
  if (L == NULL) {
    printf("List Error: calling set() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  if (isEmpty(L)) {
    printf("List Error: calling set() on empty List\n");
    exit(EXIT_FAILURE);
  }

  L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element, otherwise does
// nothing.
void moveFront(List L) {
  if (isEmpty(L)) {
    return;
  }
  L->cursor = L->front;
  L->index = 0;
}

// If L is non-empty, sets cursor under the back element, otherwise does
// nothing.
void moveBack(List L) {
  if (isEmpty(L) != 0) {
    return;
  }
  L->cursor = L->back;
  L->index = L->length - 1;
}

// If cursor is defined and not at front, move cursor one step toward the front
// of L if cursor is defined and at front, cursor becomes undefined; if cursor
// is undefined do nothing
void movePrev(List L) {
  if (L == NULL) {
    printf("List Error: calling movePrev() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == NULL) {
    return;
  }
  if (L->cursor == L->front) {
    L->cursor = NULL;
    L->index = -1;
  } else {
    L->cursor = L->cursor->prev;
    L->index--;
  }
}

// If cursor is defined and not at back, move cursor one step toward the back of
// L; if cursor is defined and at back, cursor becomes undefined; if cursor is
// undefined do nothing
void moveNext(List L) {
  if (L == NULL) {
    printf("List Error: calling moveNext() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == NULL) {
    return;
  }
  if (L->cursor == L->back) {
    L->cursor = NULL;
    L->index = -1;
    return;
  }
  if (L->cursor != L->back) {
    L->cursor = L->cursor->next;
    L->index++;
  }
}

// Insert new element into L. If L is non-empty, insertion takes place before
// front element.
void prepend(List L, int x) {
  Node N = newNode(x);

  if (L == NULL) {
    printf("List Error: calling prepend() on NULL Queue reference\n");
    exit(EXIT_FAILURE);
  }

  if (isEmpty(L)) {
    L->front = L->back = N;
  } else {
    L->front->prev = N;
    N->next = L->front;
    L->front = N;
  }
  L->length++;
  L->index++;
}

// Insert new element into L. If L is non-empty, insertion takes place after
// back element.
void append(List L, int x) {
  Node N = newNode(x);

  if (L == NULL) {
    printf("List Error: calling prepend() on NULL Queue reference\n");
    exit(EXIT_FAILURE);
  }

  if (isEmpty(L)) {
    L->front = L->back = N;
  } else {
    N->prev = L->back;
    L->back->next = N;
  }
  L->back = N;
  L->length++;
}

// Insert new element before cursor. Pre: length() > 0, index() >= 0
void insertBefore(List L, int x) {
  if (L == NULL) {
    printf("List Error: calling insertBefore() on NULL Queue reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == NULL) {
    printf("List Error: calling insertBefore() on NULL cursor\n");
    exit(EXIT_FAILURE);
  }

  if (length(L) <= 0 || index(L) < 0) {
    printf("List Error: insertBefore() preconditions have not been met\n");
    exit(EXIT_FAILURE);
  }

  if (L->cursor == L->front) {
    prepend(L, x);
  } else {
    Node new = newNode(x);
    new->prev = L->cursor->prev;
    new->next = L->cursor;
    L->cursor->prev->next = new;
    L->cursor->prev = new;
    L->length++;
    L->index++;
  }
}

// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
  if (L == NULL) {
    printf("List Error: calling insertAfter() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == NULL) {
    printf("List Error: calling insertAfter() on NULL cursor\n");
    exit(EXIT_FAILURE);
  }

  if (length(L) <= 0 || index(L) < 0) {
    printf("List Error: insertAfter() preconditions have not been met\n");
    exit(EXIT_FAILURE);
  }

  if (L->cursor == L->back) {
    append(L, x);
  } else {
    Node new = newNode(x);
    new->prev = L->cursor;
    new->next = L->cursor->next;
    L->cursor->next = new;
    L->cursor->next->prev = new;
    L->length++;
    L->index++;
  }
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
  Node N = NULL;

  if (L == NULL) {
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(L)) {
    printf("List Error: calling deleteFront() on an empty list\n");
    exit(EXIT_FAILURE);
  }

  N = L->front;
  if (length(L) > 1) {
    L->front = L->front->next;
    L->front->prev = NULL;
    L->length--;
    L->index--;
  } else {
    L->front = L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
  }
  freeNode(&N);
}
// Delete the back element. Pre: length()>0
void deleteBack(List L) {
  Node N = NULL;

  if (L == NULL) {
    printf("List Error: calling deleteBack() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(L)) {
    printf("List Error: calling deleteBack() on an empty list\n");
    exit(EXIT_FAILURE);
  }

  N = L->back;
  if (length(L) > 1) {
    L->back = L->back->prev;
    L->back->next = NULL;
    L->length--;
    if (L->cursor == N) {
      L->cursor = NULL;
      L->index = -1;
    }
  } else {
    L->front = L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
  }
  freeNode(&N);
}

// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L) {
  Node N = NULL;

  if (L == NULL) {
    printf("List Error: calling delete() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(L)) {
    printf("List Error: calling delete() on an empty list\n");
    exit(EXIT_FAILURE);
  }

  N = L->cursor;

  if (length(L) == 1) { // if only one element in list
    freeNode(&L->front);
    L->front = NULL;
    L->back = NULL;
  } else if (N == L->back) { // if cursor pointing at back of list
    L->back = L->back->prev;
    L->back->next = NULL;
    freeNode(&N);
  } else if (N == L->front) { // if cursor pointing at front list
    L->front = L->front->next;
    L->front->prev = NULL;
    freeNode(&N);
  } else { // if cursor pointing anywhere else
    N->prev->next = N->next;
    N->next->prev = N->prev;
    freeNode(&N);
  }
  L->cursor = NULL;
  L->length--;
  L->index = -1;
}
// Other operations -----------------------------------------------------------

// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE *out, List L) {
  Node N = NULL;

  if (L == NULL) {
    printf("List Error: calling printList() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  for (N = L->front; N != NULL; N = N->next) {
    fprintf(out, "%d ", N->data);
  }
  // gotta use fprintf???
}

// Returns a new List representing the same integer sequence as L. The cursor in
// the new list is undefined, regardless of the state of the cursor in L. The
// state of L is unchanged.
List copyList(List L) {
  Node N = NULL;

  if (L == NULL) {
    printf("List Error: calling copyList() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  List new = newList();
  for (N = L->front; N != NULL; N = N->next) {
    // going to be copying N into new List
    // use append broski
    append(new, N->data);
  }
  return new;
}
