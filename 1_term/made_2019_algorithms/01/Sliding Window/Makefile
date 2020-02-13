CC=g++
CFLAGS= -c -Wall -std=c++17

all: compile

run: compile
	./window

compile: main.o queue.o stack.o
	$(CC) -o window main.o queue.o stack.o

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o window
