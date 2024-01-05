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
  int *discover;
  int *finished;
  int order;
  int size;
} GraphObj;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n) {
  Graph G;
  G = malloc(sizeof(GraphObj));
  G->adj = (List *)calloc(n + 1, sizeof(List));
  G->color = (int *)malloc((n + 1) * sizeof(int));
  G->parents = (int *)malloc((n + 1) * sizeof(int));
  G->discover = (int *)malloc((n + 1) * sizeof(int));
  G->finished = (int *)malloc((n + 1) * sizeof(int));

  for (int i = 1; i < n + 1; i++) {
    G->adj[i] = newList();
    G->color[i] = white;
    G->parents[i] = NIL;
    G->discover[i] = UNDEF;
    G->finished[i] = UNDEF;
  }

  G->order = n;
  G->size = 0;
  return G;
}

void freeGraph(Graph *pG) {
  for (int i = 1; i < (*pG)->order + 1; i++) {
    freeList(&((*pG)->adj[i]));
  }
  free((*pG)->adj);
  free((*pG)->color);
  free((*pG)->parents);
  free((*pG)->discover);
  free((*pG)->finished);

  free(*pG);
  *pG = NULL;
}

// Access functions -----------------------------------------------------------

int getOrder(Graph G) { return G->order; }

int getSize(Graph G) { return G->size; }

int getParent(Graph G, int u) { return G->parents[u]; }

int getDiscover(Graph G, int u) { return G->discover[u]; }

int getFinish(Graph G, int u) { return G->finished[u]; }

// Manipulation procedures ----------------------------------------------------

// adds u to the adjacency List of v and vice verca
void addEdge(Graph G, int u, int v) {
  // adds v to the adjacency list of u
  addArc(G, u, v);

  // adds u to the adjacency list of u
  addArc(G, v, u);

  G->size -= 1;
}

void addArc(Graph G, int u, int v) {
  // check if arc is already in Graph
  for (moveFront(G->adj[u]); index(G->adj[u]) >= 0; moveNext(G->adj[u])) {
    if (get(G->adj[u]) == v) {
      return;
    }
  }

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

// visit helper function
void visit(Graph G, List S, int *time, int x) {
  G->discover[x] = ++(*time);
  G->color[x] = grey;

  moveFront(G->adj[x]);
  while (index(G->adj[x]) >= 0) {
    int y = get(G->adj[x]);
    if (G->color[y] == white) {
      G->parents[y] = x;
      visit(G, S, time, y);
    }
    moveNext(G->adj[x]);
  }

  G->color[x] = black;
  G->finished[x] = ++(*time);
  prepend(S, x);
}

// Depth First Search
void DFS(Graph G, List S) {
  for (int i = 1; i < G->order + 1; i++) {
    G->color[i] = white;
    G->parents[i] = NIL;
  }
  int time = 0;
  List copy = copyList(S);
  clear(S);
  for (moveFront(copy); index(copy) >= 0; moveNext(copy)) {
    if (G->color[get(copy)] == white) {
      visit(G, S, &time, get(copy));
    }
  }
  freeList(&copy);
}

// Other operations -----------------------------------------------------------
Graph transpose(Graph G) {
  Graph new = newGraph(G->order);
  for (int i = 1; i < G->order + 1; i++) {
    moveFront(G->adj[i]);
    while (index(G->adj[i]) >= 0) {
      addArc(new, get(G->adj[i]), i);
      moveNext(G->adj[i]);
    }
  }
  return new;
}

Graph copyGraph(Graph G) {
  Graph new = newGraph(G->order);
  for (int i = 1; i < G->order + 1; i++) {
    moveFront(G->adj[i]);
    while (index(G->adj[i]) >= 0) {
      addArc(new, i, get(G->adj[i]));
      moveNext(G->adj[i]);
    }
  }
  return new;
}

void printGraph(FILE *out, Graph G) {
  for (int i = 1; i < G->order + 1; i++) {
    fprintf(out, "%d: ", i);
    printList(out, G->adj[i]);
    fprintf(out, "\n");
  }
}
