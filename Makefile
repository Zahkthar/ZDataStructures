# Compiler
CXX = gcc
CXXFLAGS = -Wall -Wextra -O0 -g# Mettre -O1 ou -O2 à la place de -g pour la version prod

# Linker
LD = ld
LIBRARY_LINKER_FLAGS = 
TESTS_LINKER_FLAGS = -lzdatastructures -lcriterion

# Library-specific
LIBRARY_NAME = ZDataStructures

LIBRARY_BUILD_FOLDER = build/library

LIBRARY_SOURCES_FOLDER = zdatastructures/src
LIBRARY_HEADERS_FOLDER = zdatastructures/include
LIBRARY_OBJECTS_FOLDER = zdatastructures/obj

LIBRARY_SRCS = $(wildcard $(LIBRARY_SOURCES_FOLDER)/*.c)
LIBRARY_OBJS = $(patsubst $(LIBRARY_SOURCES_FOLDER)/%.c, $(LIBRARY_OBJECTS_FOLDER)/%.o, $(LIBRARY_SRCS))

# Tests-specific
TESTS_BUILD_FOLDER = build/tests

TESTS_SOURCES_FOLDER = tests/src
TESTS_HEADERS_FOLDER = tests/include
TESTS_LIB_FOLDER = tests/lib

TESTS_SRCS = $(wildcard $(TESTS_SOURCES_FOLDER)/*.c)
TESTS_BINS = $(patsubst $(TESTS_SOURCES_FOLDER)/%.c, $(TESTS_BUILD_FOLDER)/%, $(TESTS_SRCS))

# Generate all
all : docs lib tests

# Generate docs
docs:
	doxygen

# Generate the lib
lib: $(LIBRARY_OBJS)
	$(CXX) -shared -o $(LIBRARY_BUILD_FOLDER)/$(LIBRARY_NAME).dll \
	-Wl,--out-implib=$(LIBRARY_BUILD_FOLDER)/$(LIBRARY_NAME).dll.a \
	-Wl,--export-all-symbols \
	-Wl,--enable-auto-import \
	$(LIBRARY_OBJS) -L $(LIBRARY_BUILD_FOLDER) $(LIBRARY_LINKER_FLAGS)
	
	$(LD) -relocatable $(LIBRARY_OBJS) -o $(LIBRARY_BUILD_FOLDER)/libzdatastructures.a

$(LIBRARY_OBJECTS_FOLDER)/%.o: $(LIBRARY_SOURCES_FOLDER)/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(LIBRARY_HEADERS_FOLDER)

# Generate the tests
tests: dlltests $(TESTS_BINS)

$(TESTS_BUILD_FOLDER)/%: $(TESTS_SOURCES_FOLDER)/%.c
	$(CXX) $(CXXFLAGS) -o $@ $< -I $(TESTS_HEADERS_FOLDER) -I $(LIBRARY_HEADERS_FOLDER) -L $(TESTS_LIB_FOLDER) -L $(TESTS_BUILD_FOLDER) $(TESTS_LINKER_FLAGS)

dlltests:
	cp $(LIBRARY_BUILD_FOLDER)/libzdatastructures.a $(TESTS_BUILD_FOLDER)

# Clean rules
clean:
	rm -f $(LIBRARY_OBJECTS_FOLDER)/*.o

mrproper: clean
	rm -r -f docs
	rm -f $(LIBRARY_BUILD_FOLDER)/*.a $(LIBRARY_BUILD_FOLDER)/*.dll
	rm -f $(TESTS_BUILD_FOLDER)/*.exe $(TESTS_BUILD_FOLDER)/libzdatastructures.a

.PHONY: all docs lib tests clean mrproper