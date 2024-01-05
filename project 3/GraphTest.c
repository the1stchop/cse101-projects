//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa3
//-----------------------------------------------------------------------------
// GraphTest.c
// Implementation file for Graph Test
//-----------------------------------------------------------------------------

#include "Graph.h"

int main(int argc, char *argv[]) {
  Graph A = newGraph(5);
  addEdge(A, 1, 2);
  addEdge(A, 1, 3);
  addEdge(A, 2, 3);
  addEdge(A, 5, 4);
  addEdge(A, 5, 1);
  printGraph(stdout, A);
  fprintf(stdout, "\n");
  Graph B = copyGraph(A);
  printGraph(stdout, B);
  printf("\n");
  Graph P = transpose(B);
  printGraph(stdout, P);
  fprintf(stdout, "\n");
  freeGraph(&A);
  freeGraph(&B);
  freeGraph(&P);

  int i, n = 8;
  List S = newList();
  Graph G = newGraph(n);
  Graph T = NULL, C = NULL;

  for (i = 1; i <= n; i++)
    append(S, i);

  addArc(G, 1, 2);
  addArc(G, 1, 5);
  addArc(G, 2, 5);
  addArc(G, 2, 6);
  addArc(G, 3, 2);
  addArc(G, 3, 4);
  addArc(G, 3, 6);
  addArc(G, 3, 7);
  addArc(G, 3, 8);
  addArc(G, 6, 5);
  addArc(G, 6, 7);
  addArc(G, 8, 4);
  addArc(G, 8, 7);
  printGraph(stdout, G);

  DFS(G, S);
  fprintf(stdout, "\n");
  fprintf(stdout, "x:  d  f  p\n");
  for (i = 1; i <= n; i++) {
    fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i),
            getParent(G, i));
  }
  fprintf(stdout, "\n");
  printList(stdout, S);
  fprintf(stdout, "\n");

  T = transpose(G);
  C = copyGraph(G);
  fprintf(stdout, "\n");
  printGraph(stdout, C);
  fprintf(stdout, "\n");
  printGraph(stdout, T);
  fprintf(stdout, "\n");

  DFS(T, S);
  fprintf(stdout, "\n");
  fprintf(stdout, "x:  d  f  p\n");
  for (i = 1; i <= n; i++) {
    fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i),
            getParent(T, i));
  }
  fprintf(stdout, "\n");
  printList(stdout, S);
  fprintf(stdout, "\n");

  freeList(&S);
  freeGraph(&G);
  freeGraph(&T);
  freeGraph(&C);

  return 0;
}