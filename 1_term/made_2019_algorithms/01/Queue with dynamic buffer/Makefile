CC=g++
CFLAGS= -c -Wall -std=c++17

all: compile

run: compile
	./queue

compile: main.o queue.o
	$(CC) -o queue main.o queue.o

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o queue
