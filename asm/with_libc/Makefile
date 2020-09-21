with_libc: with_libc.o
	gcc -Wall -Wpedantic -m32 -ggdb -o with_libc with_libc.o

with_libc.o: with_libc.asm
	nasm -f elf32 -g -F stabs with_libc.asm

