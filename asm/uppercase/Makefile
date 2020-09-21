uppercase: uppercase.o
	ld -m elf_i386 -o uppercase uppercase.o

uppercase.o: uppercase.asm
	nasm -f elf32 -g -F stabs uppercase.asm

