#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 4
#
#  make                     makes Sparce
#  make ListTest            makes ListTest
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on in7
#  make checkTest           tests GraphTest for memory leaks
#  make format              formats all files with clang
#------------------------------------------------------------------------------

BASE_SOURCES   = Matrix.c List.c
BASE_OBJECTS   = Matrix.o List.o
HEADERS        = Matrix.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

Sparse : Sparse.o $(BASE_OBJECTS)
	$(LINK) Sparse Sparse.o $(BASE_OBJECTS)

ListTest : ListTest.o List.o
	$(LINK) ListTest ListTest.o List.o

MatrixTest : MatrixTest.o $(BASE_OBJECTS)
	$(LINK) MatrixTest MatrixTest.o $(BASE_OBJECTS)

Sparse.o : Sparse.c $(HEADERS)
	$(COMPILE) Sparse.c

ListTest.o : ListTest.c List.h
	$(COMPILE) ListTest.c

MatrixTest.o : MatrixTest.c $(HEADERS)
	$(COMPILE) MatrixTest.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) Sparse ListTest MatrixTest Sparse.o ListTest.o MatrixTest.o $(BASE_OBJECTS)

checkSparse : Sparse
	$(MEMCHECK) Sparse in7 junk7

checkListTest : ListTest
	$(MEMCHECK) ListTest

checkMatrixTest : MatrixTest
	$(MEMCHECK) MatrixTest

format :
	clang-format -i -style=file *.[ch]