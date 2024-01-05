//-----------------------------------------------------------------------------
// name: Julian Chop
// cruzid: jchop
// assignment: pa1
//-----------------------------------------------------------------------------

/****************************************************************************************
 *  ListClient.c
 *  Test client for List ADT
 *****************************************************************************************/
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  List A = newList();
  List B = newList();
  List C = NULL;
  int i;

  for (i = 1; i <= 20; i++) {
    append(A, i);
    prepend(B, i);
  }

  printList(stdout, A);
  printf("\n");
  printList(stdout, B);
  printf("\n");

  for (moveFront(A); index(A) >= 0; moveNext(A)) {
    printf("%d ", get(A));
  }
  printf("\n");
  for (moveBack(B); index(B) >= 0; movePrev(B)) {
    printf("%d ", get(B));
  }
  printf("\n");

  printf("i love u <3\n");
  C = copyList(A);
  printf("hai ahi");
  printf("%s\n", equals(A, B) ? "true" : "false");
  printf("%s\n", equals(B, C) ? "true" : "false");
  printf("%s\n", equals(C, A) ? "true" : "false");

  moveFront(A);
  printf("pweeze, pweeze just let me in D:");
  for (i = 0; i < 5; i++)
    moveNext(A);       // at index 5
  insertBefore(A, -1); // at index 6
  for (i = 0; i < 9; i++)
    moveNext(A); // at index 15
  insertAfter(A, -2);
  for (i = 0; i < 5; i++)
    movePrev(A); // at index 10
  delete (A);
  printList(stdout, A);
  printf("\n");
  printf("%d\n", length(A));
  clear(A);
  printf("%d\n", length(A));

  freeList(&A);
  freeList(&B);
  freeList(&C);

  List H = newList();
  List I = newList();
  for (i = 1; i <= 10; i++) {
    append(H, i);
    prepend(I, i);
  }
  for (i = 1; i <= 10; i++) {
    deleteFront(H);
    deleteBack(I);
    printf("%d %d\n", length(H), length(I));
  }
  clear(H);
  clear(I);

  for (i = 0; i < 10; i++){
    append(H, rand());
  }
  printList(stdout, H);
  printf("\n");

  for (moveFront(H); index(H) >= 0; moveNext(H)) {
    prepend(I, get(H));
  }
  printList(stdout, I);

  freeList(&H);
  freeList(&I);
  
}

/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
21
0
*/
