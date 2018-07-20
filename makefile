# makefile

CFLAGS = -ansi -pedantic -Wall
CC = gcc

#all: compila todo el programa y elemina los archivos objeto
all: make_mp3explorer clean

#make_mp3explorer: compila todo el programa a patir de los archivos objeto de todos los archivos .c
make_mp3explorer: main.o errors.o config.o ADT_Track.o ADT_Vector.o csv.o  mp3.o mp3explorer.o xml.o 
	$(CC) $(CFLAGS) -o mp3explorer main.o errors.o config.o ADT_Track.o ADT_Vector.o csv.o mp3.o mp3explorer.o xml.o 

main.o: main.c main.h mp3explorer.h types.h errors.h config.h
	$(CC) $(CFLAGS) -o main.o -c main.c

errors.o: errors.c types.h errors.h
	$(CC) $(CFLAGS) -o errors.o -c errors.c

config.o: config.c config.h
	$(CC) $(CFLAGS) -o config.o -c config.c

ADT_Track.o: ADT_Track.c ADT_Track.h mp3.h types.h
	$(CC) $(CFLAGS) -o ADT_Track.o -c ADT_Track.c

ADT_Vector.o: ADT_Vector.c ADT_Vector.h types.h xml.h csv.h
	$(CC) $(CFLAGS) -o ADT_Vector.o -c ADT_Vector.c

csv.o: csv.c csv.h
	$(CC) $(CFLAGS) -o csv.o -c csv.c

mp3explorer.o: mp3explorer.c types.h errors.h main.h ADT_Vector.h ADT_Track.h config.h
	$(CC) $(CFLAGS) -o mp3explorer.o -c mp3explorer.c

xml.o: xml.c xml.h
	$(CC) $(CFLAGS) -o xml.o -c xml.c

mp3.o: mp3.c mp3.h ADT_Track.h types.h
	$(CC) $(CFLAGS) -o mp3.o -c mp3.c

#clean: elemina los archivos objeto compilados
clean:
	rm *.o

