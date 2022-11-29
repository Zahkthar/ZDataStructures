CXX = gcc
CXXFLAGS = -Wall -Wextra -O0 -g# Mettre -O1 ou -O2 à la place de -g pour la version prod

LINKER_FLAGS =

HEADERS_LOCALISATION = include
LIB_LOCALISATION = lib

EXEC = ZDataStructures

SRC_FOLDER = src
OBJ_FOLDER = obj

SRCS = $(wildcard $(SRC_FOLDER)/*.c)
OBJS = $(patsubst $(SRC_FOLDER)/%.c, $(OBJ_FOLDER)/%.o, $(SRCS))

all : program

docs:
	doxygen

program : $(OBJS)
	$(CXX) $(OBJS) -o bin/$(EXEC) -L $(LIB_LOCALISATION) $(LINKER_FLAGS)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(HEADERS_LOCALISATION)

clean:
	del /f /q obj\*.o

mrproper: clean
	del /f /q bin\$(EXEC).exe
	
.PHONY: all docs lib program clean mrproper