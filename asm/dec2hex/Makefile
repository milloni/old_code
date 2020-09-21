CC = gcc
CFLAGS = -Wall -Wpedantic -m32 -ggdb
ASM = nasm
ASMFLAGS = -f elf32 -g -F dwarf

dec2hex: dec2hex.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.asm
	$(ASM) $(ASMFLAGS) $<

