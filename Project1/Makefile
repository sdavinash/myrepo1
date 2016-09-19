IDIR = hdrdir
CC = gcc
CFLAGS = -I$(IDIR) -MMD -g
CCFLAGS = -O0 -Wall $(CFLAGS)
LDFLAGS = -Wl,-Map,output.map



OBJS = $(ODIR)/revstr.o $(ODIR)/hw1.o
PPFS = $(PDIR)/revstr.i $(PDIR)/hw1.i
ASMS = $(ADIR)/revstr.s $(ADIR)/hw1.s
SRC = $(SDIR)/revstr.c $(SDIR)/hw1.c

ODIR = objdir/
SDIR = srcdir/
PDIR = predir/
ADIR = asmdir/

-include sources.mk


ifeq ($(trgt),bbb)
	CC = arm-linux-gnueabihf-gcc
else ifeq ($(trgt),frdm)
	CC = arm-none-eabi-gcc
endif



$(ODIR)%.o: $(SDIR)%.c 
	$(CC) -c -o $@ $< $(CCFLAGS)
build : $(OBJS)	
	$(CC) -o $@ $^ $(CCFLAGS) $(LDFLAGS)
	@echo "size of the executable"
	du -h $@
	objdump -Sx build > build.asm

$(PDIR)%.i: $(SDIR)%.c
	$(CC) -E -o $@ $< $(CCFLAGS)
file.i: $(PPFS)
	$(CC) -o $@ $^ $(CCFLAGS)
	@echo "size of the preprocesses file"
	du -h $@

$(ADIR)%.s: $(SDIR)%.c
	$(CC) -S -o $@ $< $(CCFLAGS)
file.s: $(ASMS)
	$(CC) -o $@ $^ $(CCFLAGS)
	@echo "size of the asm file"
	du -h $@

compile_all:
	

upload: build
	scp build root@192.168.7.2:/home/debian/bin




.PHONY: compile_all clean build file.i file.s upload compile_all objdump

clean:
	rm -f $(ODIR)*.o $(PDIR)*.i $(ADIR)*.s build  file.* *.map *.asm

