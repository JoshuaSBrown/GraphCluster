CC=g++
CFLAGS = -std=c++11 -Wall -Wextra 

ALL: test_BranchClass

test_BranchClass : test_BranchClass.cpp BranchClass.o EdgeClass.o
	$(CC) $(CFLAGS) -o test_BranchClass test_BranchClass.cpp BranchClass.o EdgeClass.o

EdgeClass.o : ../CPP_EdgeClass/EdgeClass.cpp
	$(CC) $(CFLAGS) -c ../CPP_EdgeClass/EdgeClass.cpp

BranchClass.o : BranchClass.cpp
	$(CC) $(CFLAGS) -c BranchClass.cpp

.PHONY : clean
clean : 
	$(RM) *.o test_BranchClass
