CC=g++
CFLAGS= -c -Wall -std=c++17

test_colomns: sum_by_columns.o timer.o
	$(CC) -o test_colomns sum_by_columns.o timer.o
	./test_colomns

test_rows: sum_by_rows.o timer.o
	$(CC) -o test_rows sum_by_rows.o timer.o
	./test_rows

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o test_colomns test_rows
