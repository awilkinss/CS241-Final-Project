TARGETS = driver

CFLAGS = -g -pedantic -Wall - Wextra -std=c99

CC = gcc

all: $(TARGETS)

read.o: read.c
	$(CC) $(CFLAGS) -c read.c

music.o: music.c
	$(CC) $(CFLAGS) -c music.c

driver: read.o music.o
	$(CC) $(CFLAGS) -o driver read.o music.o driver.c

clean:
	rm -f $(TARGETS) *.o *~
