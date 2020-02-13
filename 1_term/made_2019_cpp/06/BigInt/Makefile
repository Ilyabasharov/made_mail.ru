CC=g++
CFLAGS= -c -Wall -std=c++17

run: compile_run
	./big_int

test: compile_test
	./big_int

compile_run: big_int.o main.o extra_functions.o
	$(CC) -o big_int big_int.o main.o extra_functions.o

compile_test: big_int.o tests.o extra_functions.o
	$(CC) -o big_int big_int.o tests.o extra_functions.o

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o big_int
