CC= g++
CFLAGS= -c -Wall -std=c++17

run: compile
	./tree

compile: main.o binary_tree.o
	$(CC) -o tree main.o binary_tree.o

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o tree
