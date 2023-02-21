CC = gcc
CFLAGS = -Wall -Werror

all: search

search: search.o
	$(CC) $(CFLAGS) -o search search.o

search.o: search.c
	$(CC) $(CFLAGS) -c search.c

clean:
	rm -f search *.o

