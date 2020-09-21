translate: translate.o
	ld -m elf_i386 -o translate translate.o

translate.o: translate.asm
	nasm -f elf32 -g -F stabs translate.asm

