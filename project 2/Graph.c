//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa2
//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
#include "Graph.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define white 1
#define grey 2
#define black 3

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct GraphObj {
  List *adj;
  int *color;
  int *parents;
  int *distance;
  int order;
  int size;
  int source;
} GraphObj;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n) {
  Graph G;
  G = malloc(sizeof(GraphObj));
  G->adj = (List *)calloc(n + 1, sizeof(List));
  G->color = (int *)malloc((n + 1) * sizeof(int));
  G->parents = (int *)malloc((n + 1) * sizeof(int));
  G->distance = (int *)malloc((n + 1) * sizeof(int));

  for (int i = 1; i < n + 1; i++) {
    G->adj[i] = newList();
    G->color[i] = white;
    G->parents[i] = NIL;
    G->distance[i] = INF;
  }

  G->order = n;
  G->size = 0;
  G->source = NIL;
  return G;
}

void freeGraph(Graph *pG) {
  for (int i = 1; i < (*pG)->order + 1; i++) {
    freeList(&((*pG)->adj[i]));
  }
  free((*pG)->adj);
  free((*pG)->color);
  free((*pG)->parents);
  free((*pG)->distance);

  free(*pG);
  *pG = NULL;
}

// Access functions -----------------------------------------------------------

int getOrder(Graph G) { return G->order; }

int getSize(Graph G) { return G->size; }

int getSource(Graph G) { return G->source; }

int getParent(Graph G, int u) { return G->parents[u]; }

int getDist(Graph G, int u) { return G->distance[u]; }

void getPath(List L, Graph G, int u) {
  if (u == G->source) {
    append(L, G->source);
  } else if (G->parents[u] == NIL) {
    append(L, NIL);
  } else {
    getPath(L, G, G->parents[u]);
    append(L, u);
  }
}

// Manipulation procedures ----------------------------------------------------
void makeNull(Graph G) {
  for (int i = 1; i < G->order + 1; i++) {
    clear(G->adj[i]);
    G->color[i] = white;
    G->parents[i] = NIL;
    G->distance[i] = INF;
  }
  G->size = 0;
}

// adds u to the adjacency List of v and vice verca
void addEdge(Graph G, int u, int v) {
  // adds v to the adjacency list of u
  addArc(G, u, v);

  // adds u to the adjacency list of u
  addArc(G, v, u);

  G->size -= 1;
}

void addArc(Graph G, int u, int v) {
  // adding v to u.
  if (length(G->adj[u]) == 0 || v < front(G->adj[u])) {
    prepend(G->adj[u], v);
  } else {
    moveFront(G->adj[u]);
    while (v > get(G->adj[u]) && get(G->adj[u]) != back(G->adj[u])) {
      moveNext(G->adj[u]);
    }
    if (v < get(G->adj[u])) {
      insertBefore(G->adj[u], v);
    } else {
      insertAfter(G->adj[u], v);
    }
  }
  G->size += 1;
}

// Breadth First Search
void BFS(Graph G, int s) {
  for (int i = 1; i < G->order + 1; i++) {
    G->color[i] = white;
    G->parents[i] = NIL;
    G->distance[i] = INF;
  }

  G->source = s;
  G->color[s] = grey;
  G->distance[s] = 0;
  G->parents[s] = NIL;
  List Q = newList();
  append(Q, s);
  while (length(Q) != 0) {
    moveFront(Q);
    int x = get(Q);
    deleteFront(Q);

    moveFront(G->adj[x]);
    for (int i = 0; i < length(G->adj[x]); i++) {
      int y = get(G->adj[x]);
      if (G->color[y] == white) {
        G->color[y] = grey;
        G->distance[y] = G->distance[x] + 1;
        G->parents[y] = x;
        append(Q, y);
      }
      moveNext(G->adj[x]);
    }
    G->color[x] = black;
  }
  freeList(&Q);
}

// Other operations -----------------------------------------------------------
void printGraph(FILE *out, Graph G) {
  for (int i = 1; i < G->order + 1; i++) {
    fprintf(out, "%d: ", i);
    printList(out, G->adj[i]);
    fprintf(out, "\n");
  }
}
