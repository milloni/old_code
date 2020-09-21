test-prime: test-prime.o
	gcc -m32 -ggdb -o test-prime test-prime.o

test-prime.o: test-prime.asm
	nasm -f elf32 -o test-prime.o test-prime.asm

