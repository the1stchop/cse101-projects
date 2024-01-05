#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 6
#
#  make                     makes Arithmetic
#  make BigIntegerClient    makes BigIntegerClient
#  make ListClient          makes ListClient
#  make clean               removes all binaries
#  make ArithmeticCheck     runs Arithmetic in valgrind on in4 junk4
#  make BigIntegerCheck     runs BigIntegerTest in valgrind
#  make ListCheck           runs ListTest in valgrind
#------------------------------------------------------------------------------
BASE_SOURCES   = List.cpp BigInteger.cpp
BASE_OBJECTS   = List.o BigInteger.o
HEADERS        = List.h BigInteger.h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full


Arithmetic : Arithmetic.o $(BASE_OBJECTS)
	$(LINK) Arithmetic Arithmetic.o $(BASE_OBJECTS) 

ListTest : ListTest.o List.o
	$(LINK) ListTest ListTest.o List.o

BigIntegerTest : BigIntegerTest.o $(BASE_OBJECTS)
	$(LINK) BigIntegerTest BigIntegerTest.o $(BASE_OBJECTS)

BigIntegerClient : BigIntegerClient.o $(BASE_OBJECTS)
	$(LINK) BigIntegerClient BigIntegerClient.o $(BASE_OBJECTS)

Arithmetic.o : Arithmetic.cpp $(HEADERS)
	$(COMPILE) Arithmetic.cpp

ListTest.o : ListTest.cpp List.h
	$(COMPILE) ListTest.cpp

BigIntegerTest.o : BigIntegerTest.cpp $(HEADERS)
	$(COMPILE) BigIntegerTest.cpp

BigIntegerClient.o : BigIntegerClient.cpp $(HEADERS)
	$(COMPILE) BigIntegerClient.cpp

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) Arithmetic ListTest BigIntegerTest BigIntegerClient Arithmetic.o ListTest.o BigIntegerTest.o BigIntegerClient.o $(BASE_OBJECTS)

check1 : ListTest
	valgrind --leak-check=full ListTest

check2 : Arithmetic
	valgrind --leak-check=full Arithmetic 35

format :
	clang-format -i -style=file *.[ch]