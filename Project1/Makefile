CC = gcc
CFLAGS = -I.
DEPS = hw1.h

%.o: %.c $(DEPS)
	$(CC) -c -0 $@ $< $(CFLAGS)

revstring: revstr.o hw1.o
	$(CC) -o revstring revstr.o hw1.o $(CFLAGS)
