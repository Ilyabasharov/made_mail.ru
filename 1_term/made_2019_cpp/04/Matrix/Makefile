CC=g++
CFLAGS= -c -Wall -std=c++17

test: compile
	./matrix

compile: matrix.o tests.o main.o
	$(CC) -o matrix matrix.o tests.o main.o

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o matrix
