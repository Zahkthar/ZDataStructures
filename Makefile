CXX = gcc
CXXFLAGS = -Wall -Wextra -O0 -g# Mettre -O1 ou -O2 à la place de -g pour la version prod

LINKER_FLAGS = 
TESTS_LINKER_FLAGS = -lcriterion

HEADERS_LOCALISATION = include
LIB_LOCALISATION = lib

EXEC = ZDataStructures

SRC_FOLDER = src
OBJ_FOLDER = obj
SRCS = $(wildcard $(SRC_FOLDER)/*.c)
OBJS = $(patsubst $(SRC_FOLDER)/%.c, $(OBJ_FOLDER)/%.o, $(SRCS))

TESTS_FOLDER = tests
TESTS = $(wildcard $(TESTS_FOLDER)/src/*.c)
TESTBINS = $(patsubst $(TESTS_FOLDER)/src/%.c, $(TESTS_FOLDER)/bin/%, $(TESTS))

all : docs program tests

docs:
	doxygen


program : $(OBJS)
	$(CXX) $(OBJS) -o bin/$(EXEC) -L $(LIB_LOCALISATION) $(LINKER_FLAGS)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(HEADERS_LOCALISATION)


tests: $(LIB_LOCALISATION) $(TESTS_FOLDER)/bin $(TESTBINS)
	
$(TESTS_FOLDER)/bin/%: $(TESTS_FOLDER)/src/%.c
	$(CXX) $(CXXFLAGS) $< $(OBJS:obj/main.o=) -o $@ -I $(HEADERS_LOCALISATION) -L $(LIB_LOCALISATION) $(TESTS_LINKER_FLAGS)

$(TESTS_FOLDER)/bin:
	mkdir $@


clean:
	del /f /q obj\*.o

mrproper: clean
	del /f /q bin\$(EXEC).exe
	
.PHONY: all docs program tests clean mrproper