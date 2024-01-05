//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa4
//-----------------------------------------------------------------------------
//  MatrixClient.c
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include "Matrix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int n = 5;
  Matrix ee = newMatrix(n);
  printf("%d\n", NNZ(ee));
  changeEntry(ee, 1, 1, 1);
  printf("%d\n", NNZ(ee));
  changeEntry(ee, 1, 2, 4);
  printf("%d\n", NNZ(ee));
  changeEntry(ee, 1, 2, 10);
  printf("%d\n", NNZ(ee));
  printMatrix(stdout, ee);

  freeMatrix(&ee);

  Matrix A = newMatrix(n);
  changeEntry(A, 2, 1, 2);
  changeEntry(A, 3, 1, 5);
  changeEntry(A, 1, 2, 2);
  changeEntry(A, 1, 3, 5);
  changeEntry(A, 1, 1, 4);
  changeEntry(A, 2, 2, 2);
  changeEntry(A, 2, 5, 0);
  changeEntry(A, 2, 3, 0);
  changeEntry(A, 3, 3, 5);

  printMatrix(stdout, A);
  printf("%d\n", NNZ(A));

  Matrix B = copy(A);
  printMatrix(stdout, B);
  printf("%d\n", NNZ(B));

  Matrix C = transpose(B);
  printMatrix(stdout, C);
  printf("%d\n", NNZ(C));

  Matrix D = sum(A, A);
  printMatrix(stdout, A);
  printMatrix(stdout, D);

  Matrix E = product(A, A);
  printMatrix(stdout, E);

  freeMatrix(&A);
  freeMatrix(&B);
  freeMatrix(&C);
  freeMatrix(&D);
  freeMatrix(&E);

  return EXIT_SUCCESS;
}