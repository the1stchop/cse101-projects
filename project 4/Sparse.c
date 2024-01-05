//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa4
//-----------------------------------------------------------------------------
// Sparse.c
// Implementation file for Sparse
//-----------------------------------------------------------------------------

#include "List.h"
#include "Matrix.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *infile, *outfile;

  // check command line for correct number of arguments
  if (argc != 3) {
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }

  // open files for reading and writing
  infile = fopen(argv[1], "r");
  if (infile == NULL) {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }

  outfile = fopen(argv[2], "w");
  if (outfile == NULL) {
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

  // read size of Matrix, Nonzero A, and Nonzero B
  int n, nA, nB;
  fscanf(infile, "%d%d%d", &n, &nA, &nB);
  printf("%d %d %d\n", n, nA, nB);

  // create Matrix A and B
  Matrix A = newMatrix(n);
  Matrix B = newMatrix(n);

  // read Entries and place into Matrices
  int row, col;
  double val;

  for (int i = 0; i < nA; i++) {
    fscanf(infile, "%d%d%lf", &row, &col, &val);
    printf("%d %d %lf\n", row, col, val);
    changeEntry(A, row, col, val);
  }

  for (int i = 0; i < nB; i++) {
    fscanf(infile, "%d%d%lf", &row, &col, &val);
    changeEntry(B, row, col, val);
  }

  // print Matrix A and Matrix B
  fprintf(outfile, "A has %d non-zero entries: \n", NNZ(A));
  printMatrix(outfile, A);
  fprintf(outfile, "\n");
  fprintf(outfile, "B has %d non-zero entries: \n", NNZ(B));
  printMatrix(outfile, B);
  fprintf(outfile, "\n");

  // print (1.5)*A and (1.5)*B
  Matrix scalA = scalarMult(1.5, A);
  fprintf(outfile, "(1.5)*A = \n");
  printMatrix(outfile, scalA);
  fprintf(outfile, "\n");

  // print A+B and A+A
  Matrix sumAB = sum(A, B);
  Matrix sumAA = sum(A, A);
  fprintf(outfile, "A+B = \n");
  printMatrix(outfile, sumAB);
  fprintf(outfile, "\n");
  fprintf(outfile, "A+A = \n");
  printMatrix(outfile, sumAA);
  fprintf(outfile, "\n");

  // print B-A and A-A
  Matrix diffBA = diff(B, A);
  Matrix diffAA = diff(A, A);
  fprintf(outfile, "B-A = \n");
  printMatrix(outfile, diffBA);
  fprintf(outfile, "\n");
  fprintf(outfile, "A-A = \n");
  printMatrix(outfile, diffAA);
  fprintf(outfile, "\n");

  // print Transpose A
  Matrix transA = transpose(A);
  fprintf(outfile, "Transpose(A) = \n");
  printMatrix(outfile, transA);
  fprintf(outfile, "\n");

  // print A*B and B*B
  Matrix prodAB = product(A, B);
  Matrix prodBB = product(B, B);
  fprintf(outfile, "A*B = \n");
  printMatrix(outfile, prodAB);
  fprintf(outfile, "\n");
  fprintf(outfile, "B*B = \n");
  printMatrix(outfile, prodBB);
  fprintf(outfile, "\n");

  // freeing Matrices
  freeMatrix(&A);
  freeMatrix(&B);
  freeMatrix(&scalA);
  freeMatrix(&sumAA);
  freeMatrix(&sumAB);
  freeMatrix(&diffBA);
  freeMatrix(&diffAA);
  freeMatrix(&transA);
  freeMatrix(&prodAB);
  freeMatrix(&prodBB);

  // closing files
  fclose(infile);
  fclose(outfile);
}
