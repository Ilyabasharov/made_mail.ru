CC=g++
CFLAGS= -c -Wall -std=c++17

all: run

run: compile
	./stat

compile: main.o quick_select.o
	$(CC) -o stat main.o quick_select.o

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o stat
