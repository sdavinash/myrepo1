IDIR = hdrdir
CC = gcc
CFLAGS = -I$(IDIR) -MMD -g
CCFLAGS = -O0 -Wall $(CFLAGS)
LDFLAGS = -Wl,-Map,output.map

odump = objdump

VPATH = srcdir/

-include sources.mk

OBJS = ${SRC:.c=.o}
PPFS = ${SRC:.c=.i}
ASMS = ${SRC:.c=.s}

ifeq ($(trgt),bbb)
	CC = arm-linux-gnueabihf-gcc
	
else ifeq ($(trgt),frdm)
	CC = arm-none-eabi-gcc
endif



$(ODIR)%.o: $(SDIR)%.c 
	$(CC) -c $< -o $@  $(CCFLAGS)
build : $(OBJS)	
	$(CC) -o project $^ $(CCFLAGS) $(LDFLAGS)
	@echo "size of the executable"
	du -h project
	

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

compile_all: $(SRC)
	$(CC) -c -o $(ODIR) $< $(CCFLAGS)

upload: build
	scp project root@192.168.7.2:/home/debian/bin




.PHONY: compile_all clean build file.i file.s upload compile_all objdump

clean:
	rm -f $(SDIR)*.o $(SDIR)*.d $(PDIR)*.i $(PDIR)*.d $(ADIR)*.s $(ADIR)*.d project  *.map $(SDIR)*.asm 

