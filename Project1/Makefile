CC = gcc
CFLAGS = -I.
DEPS = hw1.h
OBJ = revstr.o hw1.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

revstring: revstr.o hw1.o
	$(CC) -o $@ $^ $(CFLAGS)
