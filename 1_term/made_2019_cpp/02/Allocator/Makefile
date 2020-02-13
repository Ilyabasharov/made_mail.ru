CC=g++
CFLAGS= -c -Wall -std=c++17

test: compile
	./test

compile: main.o tests.o allocator.o
	$(CC) -o test main.o tests.o allocator.o

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o test
