CC= g++
CFLAGS= -c -Wall -std=c++17

run: compile
	./hash_table

compile: main.o hash_table.o hash_func.o
	$(CC) -o hash_table main.o hash_table.o hash_func.o

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o hash_table
