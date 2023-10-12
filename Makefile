# Compiler
CXX = gcc
CXXFLAGS = -Wall -Wextra -O0 -g# Mettre -O1 ou -O2 à la place de -g pour la version prod

# Linker
LINKER_FLAGS = 
TESTS_LINKER_FLAGS = -lzdatastructures -lcriterion

# General variables
HEADERS_LOCALISATION = include
LIB_LOCALISATION = lib

DLL_NAME = ZDataStructures

# Source and objects folders/files
SRC_FOLDER = src
OBJ_FOLDER = obj
SRCS = $(wildcard $(SRC_FOLDER)/*.c)
OBJS = $(patsubst $(SRC_FOLDER)/%.c, $(OBJ_FOLDER)/%.o, $(SRCS))

# Tests folder/files
TESTS_FOLDER = tests
TESTS = $(wildcard $(TESTS_FOLDER)/src/*.c)
TESTBINS = $(patsubst $(TESTS_FOLDER)/src/%.c, $(TESTS_FOLDER)/bin/%, $(TESTS))

# Generate all
all : docs lib tests

# Generate docs
docs:
	doxygen

# Generate the lib
lib: $(OBJS)
	$(CXX) -shared -o $(LIB_LOCALISATION)/$(DLL_NAME).dll \
	-Wl,--out-implib=$(LIB_LOCALISATION)/$(DLL_NAME).dll.a \
	-Wl,--export-all-symbols \
	-Wl,--enable-auto-import \
	$(OBJS) -L $(LIB_LOCALISATION) $(LINKER_FLAGS)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(HEADERS_LOCALISATION)

# Generate the tests
tests: $(TESTBINS) dlltests $(TESTS_FOLDER)/bin

$(TESTS_FOLDER)/bin/%: $(TESTS_FOLDER)/src/%.c
	$(CXX) $(CXXFLAGS) $< -o $@ -I $(HEADERS_LOCALISATION) -L $(LIB_LOCALISATION) $(TESTS_LINKER_FLAGS)

$(TESTS_FOLDER)/bin:
	mkdir $@

dlltests:
	cp $(LIB_LOCALISATION)/$(DLL_NAME).dll $(TESTS_FOLDER)/bin

# Clean rules
clean:
	del /f /q obj/*.o

mrproper: clean
	del /f /q $(LIB_LOCALISATION)/$(DLL_NAME).dll

.PHONY: all docs lib tests clean mrproper