//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa2
//-----------------------------------------------------------------------------
// FindPath.c
// Implementation file for FindPath
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
  Graph Graph = newGraph(n);

  // read vertices and place in graph
  int u, v;
  fscanf(infile, "%d%d", &u, &v);
  while (u != 0 || v != 0) {
    addEdge(Graph, u, v);
    fscanf(infile, "%d%d", &u, &v);
  }

  // print Graph
  printGraph(outfile, Graph);
  fprintf(outfile, "\n");

  // run BFS and find path for each source and destination
  List path = newList();
  fscanf(infile, "%d%d", &u, &v);
  while (u != 0 || v != 0) {
    BFS(Graph, u);
    getPath(path, Graph, v);

    // print path
    if (getDist(Graph, v) == -1) {
      fprintf(outfile, "The distance from %d to %d is infinity\n", u, v);
      fprintf(outfile, "No %d-%d path exists\n\n", u, v);
    } else {
      fprintf(outfile, "The distance from %d to %d is %d\n", u, v,
              getDist(Graph, v));
      fprintf(outfile, "A shortest %d-%d path is: ", u, v);
      printList(outfile, path);
      fprintf(outfile, "\n\n");
    }

    // reset list
    clear(path);

    // scan new source and destination
    fscanf(infile, "%d%d", &u, &v);
  }

  // freeing Graph and list
  freeGraph(&Graph);
  freeList(&path);

  // closing files
  fclose(infile);
  fclose(outfile);
}
