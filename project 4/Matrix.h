//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa4
//-----------------------------------------------------------------------------
// Matrix.h
// Header file for Matrix ADT
//-----------------------------------------------------------------------------
#ifndef Matrix_H_INCLUDE_
#define Matrix_H_INCLUDE_
#include "List.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Exported types -------------------------------------------------------------
typedef struct MatrixObj *Matrix;

// Constructors-Destructors ---------------------------------------------------
Matrix newMatrix(int n);

void freeMatrix(Matrix *pM);

// Access functions -----------------------------------------------------------
int size(Matrix M);

int NNZ(Matrix M);

int equals(Matrix A, Matrix B);

// Manipulation procedures ----------------------------------------------------
void makeZero(Matrix M);

void changeEntry(Matrix M, int i, int j, double x);

// Matrix Arithmetic procedures -----------------------------------------------
Matrix copy(Matrix A);

Matrix transpose(Matrix A);

Matrix scalarMult(double x, Matrix A);

Matrix sum(Matrix A, Matrix B);

Matrix diff(Matrix A, Matrix B);

Matrix product(Matrix A, Matrix B);

void printMatrix(FILE *out, Matrix M);

#endif