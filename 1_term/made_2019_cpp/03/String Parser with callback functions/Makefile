CC=g++
CFLAGS= -c -Wall -std=c++17

test: compile
	./parser

compile: parser.o tests.o main.o
	$(CC) -o parser parser.o tests.o main.o

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o parser
