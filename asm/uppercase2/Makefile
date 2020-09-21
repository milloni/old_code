uppercase2: uppercase2.o
	ld -m elf_i386 -o uppercase2 uppercase2.o

uppercase2.o: uppercase2.asm
	nasm -f elf32 -g -F stabs uppercase2.asm

