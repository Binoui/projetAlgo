CC=gcc
CFLAGS= -W -Wall -ansi -g

libtable64: table.o
	ar cr $@.a $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o test_table
