CC=gcc
CFLAG=-Wall -g
LIBS=$home/Document/TP/projet_Algo/MODULE_IMAGE/
OBJ=main.o 
OUTPUT=testimage

$(OUTPUT): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS) -limage 

clean:
	rm -f $(OUTPUT) $(OBJ)

main.o: main.c image.h objet.h exit_if.h classe.h point.h move_type.h \
  type_obj.h
	$(CC) $(CFLAG) -c main.c


