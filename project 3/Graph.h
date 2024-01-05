//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa3
//-----------------------------------------------------------------------------
// Graph.h
// header file for Graph ADT
//-----------------------------------------------------------------------------

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include "List.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define UNDEF -1
#define NIL 0

// Exported types -------------------------------------------------------------
typedef struct GraphObj *Graph;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n);
void freeGraph(Graph *pG);

// Access functions -----------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

// Manipulation procedures ----------------------------------------------------
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

// Other operations -----------------------------------------------------------
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE *out, Graph G);

#endif