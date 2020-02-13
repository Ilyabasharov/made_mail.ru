CC= g++
CFLAGS= -c -Wall -std=c++17

run: compile
	./haffman

compile: stream.o main.o bits_workers.o
	$(CC) -o haffman stream.o main.o bits_workers.o

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o haffman graph.gv
