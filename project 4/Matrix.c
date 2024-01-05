//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa4
//-----------------------------------------------------------------------------
// Matrix.c
// Implementation file for Matrix ADT
//-----------------------------------------------------------------------------
#include "Matrix.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// structs --------------------------------------------------------------------

typedef struct EntryObj *Entry;

// private EntryObj type
typedef struct EntryObj {
  int col;
  double val;
} EntryObj;

typedef struct MatrixObj {
  List *row;
  int size;
  int nonZero;
} MatrixObj;

// Constructors-Destructors ---------------------------------------------------

// Creates and returns a new Entry
Entry newEntry(int c, double v) {
  Entry E = malloc(sizeof(EntryObj));
  E->col = c;
  E->val = v;
  return E;
}

// Frees all heap memory pointed to by *pN, set *pN to NULL.
void freeEntry(Entry *pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}

// Creates and returns a new empty Matrix.
Matrix newMatrix(int n) {
  Matrix M;
  M = malloc(sizeof(MatrixObj));

  // adding n lists to rows
  M->row = malloc(sizeof(List) * (n + 1));
  for (int i = 1; i <= n; i++) {
    M->row[i] = newList();
  }

  M->size = n;
  M->nonZero = 0;
  return M;
}

// Frees all heap memory associated with *pM and sets *pM to NULL.
void freeMatrix(Matrix *pM) {
  if (pM != NULL && *pM != NULL) {
    makeZero(*pM);
  }

  for (int i = 1; i <= (*pM)->size; i++) {
    freeList(&((*pM)->row[i]));
  }

  free((*pM)->row);
  free(*pM);
  *pM = NULL;
}

// Access functions -----------------------------------------------------------
int size(Matrix M) { return M->size; }

int NNZ(Matrix M) { return M->nonZero; }

int equals(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    printf("Matrix Error: calling equals on NULL matrix.\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    return 0;
  }
  Entry tempA, tempB;
  for (int i = 1; i <= A->size; i++) {
    moveFront(A->row[i]);
    moveFront(B->row[i]);

    if (length(A->row[i]) != length(B->row[i])) {
      return 0;
    }

    while (index(A->row[i]) >= 0 && index(B->row[i]) >= 0) {
      tempA = (Entry)(get(A->row[i]));
      tempB = (Entry)(get(B->row[i]));
      if (tempA->val != tempB->val) {
        return 0;
      }
      moveNext(A->row[i]);
      moveNext(B->row[i]);
    }
  }
  return 1;
}

// Manipulation procedures ----------------------------------------------------

// resets Matrix M to the zero matrix state
void makeZero(Matrix M) {
  if (M == NULL) {
    printf("the fuck you doin bruv\n");
  }
  Entry temp;
  for (int i = 1; i <= M->size; i++) {
    if (length(M->row[i]) != 0) {
      for (moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])) {
        temp = (Entry)(get(M->row[i]));
        freeEntry(&temp);
      }
    }
    clear(M->row[i]);
  }
  M->nonZero = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
  // check if i and j are less than or equal to n
  if (i > M->size || i < 1 || j > M->size || j < 1) {
    printf("Matrix Error: invalid entry\n");
    exit(EXIT_FAILURE);
  }

  if (length(M->row[i]) == 0) {
    if (x != 0) {
      Entry E = newEntry(j, x);
      prepend(M->row[i], E);
      M->nonZero += 1;
    }
    return;
  }

  moveFront(M->row[i]);
  Entry temp = (Entry)(get(M->row[i]));
  while (j > temp->col && index(M->row[i]) != length(M->row[i]) - 1) {
    moveNext(M->row[i]);
    temp = (Entry)(get(M->row[i]));
  }
  if (index(M->row[i]) < 0) {
    if (x != 0) {
      Entry E = newEntry(j, x);
      append(M->row[i], E);
      M->nonZero += 1;
    }
  } else if (j < temp->col) {
    if (x != 0) {
      Entry E = newEntry(j, x);
      insertBefore(M->row[i], E);
      M->nonZero += 1;
    }
  } else if (j > temp->col) {
    if (x != 0) {
      Entry E = newEntry(j, x);
      insertAfter(M->row[i], E);
      M->nonZero += 1;
    }
  } else {
    if (x != 0) {
      temp->val = x;
    } else {
      freeEntry(&temp);
      delete (M->row[i]);
      M->nonZero -= 1;
    }
  }
}

// Matrix Arithmetic procedures -----------------------------------------------
Matrix copy(Matrix A) {
  Entry temp, new;
  Matrix B = newMatrix(size(A));
  for (int i = 1; i <= size(A); i++) {
    if (length(A->row[i]) != 0) {
      for (moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])) {
        temp = (Entry)(get(A->row[i]));
        new = newEntry(temp->col, temp->val);
        append(B->row[i], new);
        B->nonZero += 1;
      }
    }
  }
  return B;
}

Matrix transpose(Matrix A) {
  Entry temp, new;
  Matrix B = newMatrix(size(A));
  for (int i = 1; i <= size(A); i++) {
    if (length(A->row[i]) != 0) {
      for (moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])) {
        temp = (Entry)(get(A->row[i]));
        new = newEntry(i, temp->val);
        append(B->row[temp->col], new);
        B->nonZero += 1;
      }
    }
  }
  return B;
}

Matrix scalarMult(double x, Matrix A) {
  Entry temp, new;
  Matrix B = newMatrix(size(A));
  for (int i = 1; i <= size(A); i++) {
    if (length(A->row[i]) != 0) {
      for (moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])) {
        temp = (Entry)(get(A->row[i]));
        new = newEntry(temp->col, x * temp->val);
        append(B->row[i], new);
        B->nonZero += 1;
      }
    }
  }
  return B;
}

Matrix sum(Matrix A, Matrix B) {
  if (size(A) != size(B)) {
    printf("Matrix Error: calling sum() on two different sized Matrices.\n");
    exit(EXIT_FAILURE);
  }

  // if matrices are equal
  if (equals(A, B) == 1) {
    Matrix C = scalarMult(2, A);
    return C;
  }

  Entry tempA, tempB, new;
  Matrix C = newMatrix(size(A));

  for (int i = 1; i <= size(A); i++) {
    moveFront(A->row[i]);
    moveFront(B->row[i]);

    while (index(A->row[i]) >= 0 && index(B->row[i]) >= 0) {
      tempA = (Entry)(get(A->row[i]));
      tempB = (Entry)(get(B->row[i]));

      if (tempA->col < tempB->col) {
        new = newEntry(tempA->col, tempA->val);
        append(C->row[i], new);
        C->nonZero += 1;
        moveNext(A->row[i]);
      } else if (tempA->col > tempB->col) {
        new = newEntry(tempB->col, tempB->val);
        append(C->row[i], new);
        C->nonZero += 1;
        moveNext(B->row[i]);
      }
      if (tempA->col == tempB->col) {
        if (tempA->val + tempB->val != 0) {
          new = newEntry(tempA->col, tempA->val + tempB->val);
          append(C->row[i], new);
          C->nonZero += 1;
        }
        moveNext(A->row[i]);
        moveNext(B->row[i]);
      }
    }

    // flush rest of the shit
    while (index(A->row[i]) >= 0) {
      tempA = (Entry)(get(A->row[i]));
      new = newEntry(tempA->col, tempA->val);
      append(C->row[i], new);
      C->nonZero += 1;
      moveNext(A->row[i]);
    }
    while (index(B->row[i]) >= 0) {
      tempB = (Entry)(get(B->row[i]));
      new = newEntry(tempB->col, tempB->val);
      append(C->row[i], new);
      C->nonZero += 1;
      moveNext(B->row[i]);
    }
  }

  return C;
}

Matrix diff(Matrix A, Matrix B) {
  if (size(A) != size(B)) {
    printf("Matrix Error: calling sum() on two different sized Matrices.\n");
    exit(EXIT_FAILURE);
  }

  Entry tempA, tempB, new;
  Matrix C = newMatrix(size(A));

  // if matrices are equal
  if (equals(A, B) == 1) {
    return C;
  }

  for (int i = 1; i <= size(A); i++) {
    moveFront(A->row[i]);
    moveFront(B->row[i]);

    while (index(A->row[i]) >= 0 && index(B->row[i]) >= 0) {
      tempA = (Entry)(get(A->row[i]));
      tempB = (Entry)(get(B->row[i]));

      if (tempA->col < tempB->col) {
        new = newEntry(tempA->col, tempA->val);
        append(C->row[i], new);
        C->nonZero += 1;
        moveNext(A->row[i]);
      } else if (tempA->col > tempB->col) {
        new = newEntry(tempB->col, -tempB->val);
        append(C->row[i], new);
        C->nonZero += 1;
        moveNext(B->row[i]);
      }
      if (tempA->col == tempB->col) {
        if (tempA->val - tempB->val != 0) {
          new = newEntry(tempA->col, tempA->val - tempB->val);
          append(C->row[i], new);
          C->nonZero += 1;
        }
        moveNext(A->row[i]);
        moveNext(B->row[i]);
      }
    }

    // flush rest of the shit
    while (index(A->row[i]) >= 0) {
      tempA = (Entry)(get(A->row[i]));
      new = newEntry(tempA->col, tempA->val);
      append(C->row[i], new);
      C->nonZero += 1;
      moveNext(A->row[i]);
    }
    while (index(B->row[i]) >= 0) {
      tempB = (Entry)(get(B->row[i]));
      new = newEntry(tempB->col, -tempB->val);
      append(C->row[i], new);
      C->nonZero += 1;
      moveNext(B->row[i]);
    }
  }

  return C;
}

// helper function for product().
double vectorDot(List P, List Q) {
  Entry tempP, tempQ;
  double dotProd = 0;
  moveFront(P);
  moveFront(Q);
  while (index(P) >= 0 && index(Q) >= 0) {
    tempP = (Entry)(get(P));
    tempQ = (Entry)(get(Q));

    if (tempP->col < tempQ->col) {
      moveNext(P);
    } else if (tempP->col > tempQ->col) {
      moveNext(Q);
    } else {
      dotProd += tempP->val * tempQ->val;
      moveNext(P);
      moveNext(Q);
    }
  }
  return dotProd;
}

Matrix product(Matrix A, Matrix B) {
  if (size(A) != size(B)) {
    printf("Matrix Error: calling sum() on two different sized Matrices.\n");
    exit(EXIT_FAILURE);
  }

  Entry new;
  Matrix C = newMatrix(size(A));
  Matrix T = transpose(B);

  for (int i = 1; i <= size(A); i++) {
    for (int j = 1; j <= size(A); j++) {
      double x = vectorDot(A->row[i], T->row[j]);
      if (x != 0) {
        new = newEntry(j, x);
        append(C->row[i], new);
        C->nonZero += 1;
      }
    }
  }
  freeMatrix(&T);
  return C;
}

void printMatrix(FILE *out, Matrix M) {
  Entry temp;
  for (int i = 1; i <= M->size; i++) {
    if (length(M->row[i]) != 0) {
      fprintf(out, "%d: ", i);
      for (moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])) {
        temp = (Entry)(get(M->row[i]));
        fprintf(out, "(%d, %.1lf) ", temp->col, temp->val);
      }
      fprintf(out, "\n");
    }
  }
}