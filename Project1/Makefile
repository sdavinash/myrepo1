CC = gcc
IDIR = hdrdir
CFLAGS = -I$(IDIR) -g -O0 -Wall


DEPS = $(IDIR)/hw1.h
OBJS = $(ODIR)/revstr.o $(ODIR)/hw1.o
PPFS = $(PDIR)/revstr.i $(PDIR)/hw1.i
ASMS = $(ADIR)/revstr.s $(ADIR)/hw1.s
SRC = $(SDIR)/revstr.c $(SDIR)/hw1.c

ODIR = objdir/
SDIR = srcdir
PDIR = predir/
ADIR = asmdir/

include sources.mk


$(ODIR)%.o: $(SDIR)%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
build : $(OBJS)	
	$(CC) -o $@ $^ $(CFLAGS)

$(PDIR)%.i: $(SDIR)%.c $(DEPS)
	$(CC) -E -o $@ $< $(CFLAGS)
file.i: $(PPFS)
	$(CC) -o $@ $^ $(CFLAGS)

$(ADIR)%.s: $(SDIR)%.c $(DEPS)
	$(CC) -S -o $@ $< $(CFLAGS)
asm.s: $(ASMS)
	$(CC) -o $@ $^ $(CFLAGS)

compile_all: $(SDIR)%.c
	$(CC) -c $^ -o $(ODIR) $(CFLAGS)

upload: build
	scp build root@192.168.7.2:/home/debian/bin



.PHONY: compile_all clean

clean:
	rm $(ODIR)*.o $(PDIR)*.i $(ADIR)*.s 

