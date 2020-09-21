eatsyscall: eatsyscall.o
	ld -m elf_i386 -o eatsyscall eatsyscall.o

eatsyscall.o: eatsyscall.asm
	nasm -f elf32 -g -F stabs eatsyscall.asm

