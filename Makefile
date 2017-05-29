CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
TDA = heap
PRUEBAS = pruebas_alumno
EXE = pruebas


all: tda testing.o main.o pruebas.o vector.o
	$(CC) $(CFLAGS) -o $(EXE) $(PRUEBAS).o $(TDA).o testing.o main.o vector_dinamico.o

tda:
	$(CC) $(CFLAGS) $(TDA).c -c

testing.o:
	$(CC) $(CFLAGS) testing.c -c

main.o:
	$(CC) $(CFLAGS) main.c -c

pruebas.o:
	$(CC) $(CFLAGS) $(PRUEBAS).c -c

vector.o:
	$(CC) $(CFLAGS) vector_dinamico.c -c

clean:
	rm $(EXE) *.o

run: all
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$(EXE)
