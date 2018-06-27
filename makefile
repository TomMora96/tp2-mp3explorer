# makefile

CFLAGS = -ansi -pedantic -Wall
CC = gcc

all: make_main clean

prueba_track: make_prueba_track

make_prueba_track: mp3.o prueba_track.o ADT_Track.o errors.o
	$(CC) $(CFLAGS) -o prueba_track prueba_track.o ADT_Track.o mp3.o errors.o

make_main: main.o errors.o config.o 
	$(CC) $(CFLAGS) -o main main.o errors.o config.o

prueba_track.o: prueba_track.c ADT_Track.h mp3.h types.h errors.h
	$(CC) $(CFLAGS) -o prueba_track.o -c prueba_track.c

main.o: main.c main.h config.h types.h
	$(CC) $(CFLAGS) -o main.o -c main.c

errors.o: errors.c types.h errors.h
	$(CC) $(CFLAGS) -o errors.o -c errors.c

config.o: config.c config.h
	$(CC) $(CFLAGS) -o config.o -c config.c

ADT_Track.o: ADT_Track.c ADT_Track.h mp3.h types.h
	$(CC) $(CFLAGS) -o ADT_Track.o -c ADT_Track.c

mp3.o: mp3.c mp3.h ADT_Track.h types.h
	$(CC) $(CFLAGS) -o mp3.o -c mp3.c

clean:
	rm *.o

