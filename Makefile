CXX = gcc
CXXFLAGS = -Wall -Wextra -g# Mettre -O1 ou -O2 à la place de -g pour la version prod

LINKER_FLAGS =

EXEC = ZDataStructures

SRC = main.c ZSinglyLinkedList.c
OBJ = $(SRC:.c=.o)

all : program docs

docs:
	doxygen

program : $(OBJ)
	$(CXX) $(LINKER_FLAGS) $(addprefix obj\, $(OBJ)) -o bin\$(EXEC)

%.o: src\%.c
	$(CXX) $(CXXFLAGS) -c $< -o obj\$@

clean:
	del /f /q obj\*.o

mrproper: clean
	del /f /q bin\$(EXEC).exe
	
.PHONY: all docs program clean mrproper