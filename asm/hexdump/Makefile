hexdump: hexdump.o
	gcc -m32 -ggdb -o hexdump hexdump.o

hexdump.o: hexdump.asm
	nasm -f elf32 -o hexdump.o hexdump.asm

