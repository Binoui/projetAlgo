CC=gcc
CFLAGS= -W -Wall -ansi -g

table: table.o
	$(CC) $< ../MODULE_IMAGE/libimage64.a -o $@.x

libtable64: table.o
	ar cr $@.a $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o test_table
