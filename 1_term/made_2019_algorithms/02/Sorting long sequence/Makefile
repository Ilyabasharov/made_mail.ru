CC= g++
CFLAGS= -c -Wall -std=c++17

run: compile_run
	./window

test: compile_test
	./window

compile_run: main.o sorted_window.o
	$(CC) -o window main.o sorted_window.o

compile_test: tests.o sorted_window.o
	$(CC) -o window tests.o sorted_window.o

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o window
