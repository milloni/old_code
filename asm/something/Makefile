something: something.o
	ld -m elf_i386 -o something something.o

something.o: something.asm
	nasm -f elf32 -g -F stabs something.asm

