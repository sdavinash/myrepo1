CFLAGS = -I.
DEPS = hw1.h
OBJ = revstr.o hw1.o
SRC = revstr.c hw1.c


ifeq ($(CC),host)
file.i: $(SRC) $(DEPS)
	gcc -E -o $@ $< $(CFLAGS)

%.o: $(SRC) $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

file.s: $(SRC) $(DEPS)
	gcc -S -o $@ $< $(CFLAGS)

build: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

else ifeq ($(CC),bbb)
file.i: %.c $(DEPS)
	arm-linux-gnueabihf-gcc -E -o $@ $< $(CFLAGS)

file.s: %.c $(DEPS)
	arm-linux-gnueabihf-gcc -S -o $@ $< $(CFLAGS)
	
%.o: %.c $(DEPS)
	arm-linux-gnueabihf-gcc -c -o $@ $< $(CFLAGS)

build: $(OBJ)
	arm-linux-gnueabihf-gcc -o $@ $^ $(CFLAGS)

else ifeq ($(CC),frdm)
file.i: %.c $(DEPS)
	arm-none-eabi-gcc -E -o $@ $< $(CFLAGS)

file.s: %.c $(DEPS)
	arm-none-eabi-gcc -S -o $@ $< $(CFLAGS)

%.o: %.c $(DEPS)
	arm-none-eabi-gcc -c -o $@ $< $(CFLAGS)

build: $(OBJ)
	arm-none-eabi-gcc -o $@ $^ $(CFLAGS)
else
.PHONY: print 
print:
	@echo "Please enter a compiler name as either of host or bbb or frdm"	
endif

.PHONY: print clean
clean:
	rm *.o *.i *.s build
