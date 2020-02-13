CC=g++
CFLAGS= -c -Wall -std=c++17

all: compile

run: ./calculator
	./calculator "$(ARGS)"

test: calculation.o tests.o
	$(CC) -o test calculation.o tests.o
	./test

compile: main.o calculation.o
	$(CC) -o calculator main.o calculation.o

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o calculator test
