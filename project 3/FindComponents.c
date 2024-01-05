//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa3
//-----------------------------------------------------------------------------
// FindComponents.c
// Implementation file for FindComponents
//-----------------------------------------------------------------------------

#include "Graph.h"
#include "List.h"

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

  // read length of Graph
  int n;
  fscanf(infile, "%d", &n);

  // create graph
  Graph G = newGraph(n);

  // read vertices and place in graph
  int u, v;
  fscanf(infile, "%d%d", &u, &v);
  while (u != 0 || v != 0) {
    addArc(G, u, v);
    fscanf(infile, "%d%d", &u, &v);
  }

  // print Graph
  fprintf(outfile, "Adjacency list representation of G:\n");
  printGraph(outfile, G);
  fprintf(outfile, "\n");

  // run DFS on Graph and transpose
  List stack = newList();
  for (int i = 1; i <= n; i++)
    append(stack, i);
  DFS(G, stack);
  Graph T = transpose(G);
  DFS(T, stack);

  // printing strong components
  int sc = 0;
  for (moveFront(stack); index(stack) >= 0; moveNext(stack)) {
    if (getParent(T, get(stack)) == NIL) {
      sc += 1;
    }
  }
  fprintf(outfile, "G contains %d strongly connected components:\n", sc);

  List x = newList();
  sc = 1;
  for (moveBack(stack); index(stack) >= 0; movePrev(stack)) {
    prepend(x, get(stack));
    if (getParent(T, get(stack)) == NIL) {
      fprintf(outfile, "Component %d: ", sc);
      printList(outfile, x);
      fprintf(outfile, "\n");
      clear(x);
      sc += 1;
    }
  }

  // freeing graphs and lists
  freeGraph(&G);
  freeGraph(&T);
  freeList(&stack);
  freeList(&x);

  // closing files
  fclose(infile);
  fclose(outfile);
}
