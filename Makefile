CXX = gcc
CXXFLAGS = -Wall -Wextra -O0 -g# Mettre -O1 ou -O2 à la place de -g pour la version prod

LINKER_FLAGS =

HEADERS_LOCALISATION = include
LIB_LOCALISATION = lib

EXEC = ZDataStructures

PROGRAM_SRC = main.c
PROGRAM_OBJ = $(PROGRAM_SRC:.c=.o)

LIB_SRC = ZSinglyLinkedList.c
LIB_OBJ = $(LIB_SRC:.c=.o)

all : docs lib program

docs:
	doxygen

lib:
	$(CXX) $(CXXFLAGS) -c include\ZSinglyLinkedList.c -o lib\ZSinglyLinkedList.o

program : $(PROGRAM_OBJ)
	$(CXX) $(LINKER_FLAGS) $(addprefix obj\, $(PROGRAM_OBJ)) $(addprefix lib\, $(LIB_OBJ)) -o bin\$(EXEC) 

%.o: src\%.c
	$(CXX) $(CXXFLAGS) -c $< -o obj\$@ -I $(HEADERS_LOCALISATION)

clean:
	del /f /q obj\*.o

mrproper: clean
	del /f /q bin\$(EXEC).exe
	
.PHONY: all docs lib program clean mrproper