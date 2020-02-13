CC=g++
CFLAGS= -c -Wall -std=c++17

all: compile

run: compile
	./dead_ends

compile: main.o heap.o
	$(CC) -o dead_ends main.o heap.o

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o dead_ends
