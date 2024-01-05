//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa2
//-----------------------------------------------------------------------------
// Graph.c
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
  List Shitter = newList();
  BFS(A, 1);
  getPath(Shitter, A, 4);
  printList(stdout, Shitter);
  printf("\n");
  freeGraph(&A);
  freeList(&Shitter);

  A = newGraph(5);
  addEdge(A, 1, 2);
  addEdge(A, 1, 3);
  addEdge(A, 2, 3);
  addEdge(A, 5, 4);
  addEdge(A, 5, 1);
  printGraph(stdout, A);
  printf("\n");
  Shitter = newList();
  BFS(A, 1);
  getPath(Shitter, A, 1);
  printList(stdout, Shitter);
  printf("\n");
  freeGraph(&A);
  freeList(&Shitter);

  int i, s, max, min, d, n = 35;
  List C = newList(); // central vertices
  List P = newList(); // peripheral vertices
  List E = newList(); // eccentricities
  Graph G = NULL;

  // Build graph G
  G = newGraph(n);
  for (i = 1; i < n; i++) {
    if (i % 7 != 0)
      addEdge(G, i, i + 1);
    if (i <= 28)
      addEdge(G, i, i + 7);
  }
  printGraph(stdout, G);
  printf("\n\n");

  addEdge(G, 9, 31);
  addEdge(G, 17, 13);
  addEdge(G, 14, 33);

  // Print adjacency list representation of G
  printGraph(stdout, G);

  // Calculate the eccentricity of each vertex
  for (s = 1; s <= n; s++) {
    BFS(G, s);
    max = getDist(G, 1);
    for (i = 2; i <= n; i++) {
      d = getDist(G, i);
      max = (max < d ? d : max);
    }
    append(E, max);
  }

  // Determine the Radius and Diameter of G, as well as the Central and
  // Peripheral vertices.
  append(C, 1);
  append(P, 1);
  min = max = front(E);
  moveFront(E);
  moveNext(E);
  for (i = 2; i <= n; i++) {
    d = get(E);
    if (d == min) {
      append(C, i);
    } else if (d < min) {
      min = d;
      clear(C);
      append(C, i);
    }
    if (d == max) {
      append(P, i);
    } else if (d > max) {
      max = d;
      clear(P);
      append(P, i);
    }
    moveNext(E);
  }

  // Print results
  printf("\n");
  printf("Radius = %d\n", min);
  printf("Central vert%s: ", length(C) == 1 ? "ex" : "ices");
  printList(stdout, C);
  printf("\n");
  printf("Diameter = %d\n", max);
  printf("Peripheral vert%s: ", length(P) == 1 ? "ex" : "ices");
  printList(stdout, P);
  printf("\n");

  // Free objects
  freeList(&C);
  freeList(&P);
  freeList(&E);
  freeGraph(&G);

  return 0;
}