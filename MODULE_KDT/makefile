CC=gcc
CFLAGS= -W -Wall -ansi -g

kdtree: mainkdtree.o kdtree.o ../MODULE_IMAGE/libimage64.a ../MODULE_TABLE/libtable64.a
	$(CC) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.x kdtree mainkdtree

