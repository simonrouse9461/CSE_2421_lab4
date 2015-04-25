%.o: %.c
	gcc -g -c -o $@ $<
all: lab4
lab4: lab4.o matrix.o
	gcc lab4.o matrix.o -o lab4 -lm
lab4.o: lab4.c matrix.h testmode.h
	gcc -c -g lab4.c -Wall
matrix.o: matrix.c matrix.h testmode.h
	gcc -c -g matrix.c -Wall
clean:
	rm -f *.o lab4 output
