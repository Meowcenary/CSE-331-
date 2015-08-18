CC= g++ #your compiler
CFLAGS=-std=c++0x -c -Wall#additional flags to pass 
LDFLAGS=
SOURCES= bst.h bst.cpp#your .c/.cpp files go here
OBJECTS=$(SOURCES:.c=.o)#any additional .o files go here
EXECUTABLE=BST#your executable name

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
