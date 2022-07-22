CXX = gcc
CXXFLAGS = -Wall -g

LINKER_FLAGS =

EXEC = ZDataStructures

all : program

program : main.o ZDataStructures.o
	$(CXX) $(LINKER_FLAGS) obj\main.o obj\ZDataStructures.o -o bin\$(EXEC)

main.o : src\main.c
	$(CXX) $(CXXFLAGS) -c src\main.c -o obj\main.o

ZDataStructures.o : src\ZDataStructures.c
	$(CXX) $(CXXFLAGS) -c src\ZDataStructures.c -o obj\ZDataStructures.o