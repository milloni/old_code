endianness: endianness.o
	ld -m elf_i386 -o endianness endianness.o

endianness.o: endianness.asm
	nasm -f elf32 -g -F stabs endianness.asm

