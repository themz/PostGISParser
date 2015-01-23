CC=g++-4.9
CFLAGS=-std=gnu++11 -c -Wall
LDFLAGS=-std=c++11
SOURCES=main.cpp parser.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=parser

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
