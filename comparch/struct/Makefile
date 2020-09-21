all: structs a

a: a.s
	gcc -std=c99 -m32 -ggdb -o a a.s

a.s: a.c
	gcc -std=c99 -m32 -ggdb -S a.c

structs: structs.o
	gcc -std=c99 -m32 -ggdb -o structs structs.o

structs.o: structs.asm
	nasm -f elf32 -o structs.o structs.asm

