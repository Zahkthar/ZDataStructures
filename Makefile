CXX = gcc
CXXFLAGS = -Wall -Wextra -O0 -g# Mettre -O1 ou -O2 à la place de -g pour la version prod

LINKER_FLAGS =

HEADERS_LOCALISATION = include

EXEC = ZDataStructures

SRC = main.c ZSinglyLinkedList.c ZDynamicArray.c
OBJ = $(SRC:.c=.o)

all : program

docs:
	doxygen

program : $(OBJ)
	$(CXX) $(LINKER_FLAGS) $(addprefix obj\, $(OBJ)) -o bin\$(EXEC) 

%.o: src\%.c
	$(CXX) $(CXXFLAGS) -c $< -o obj\$@ -I $(HEADERS_LOCALISATION)

clean:
	del /f /q obj\*.o

mrproper: clean
	del /f /q bin\$(EXEC).exe
	
.PHONY: all docs lib program clean mrproper