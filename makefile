all: trabs

trabs: trabs.o
	gcc -o trabs trabs.o

trabs.o: trabs.c
	gcc -c mainB.c mainB.h b-tree.c

clean:
	rm trabs.o trabs
