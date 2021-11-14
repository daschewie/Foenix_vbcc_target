export AS = vasmm68k_mot
export ASFLAGS = -quiet -Fvobj -nowarn=62
export CC = vc
export CFLAGS = +a2560-elf
export LD = vlink

.PHONY: all

all: io.o startup.o syscalls.o

install: all
	cp *.o ../vbcc/targets/a2560-elf/lib

clean:
	rm -f *.o

%.o: $.s
	$(AS) $(ASFLAGS) -o $@ $<

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
