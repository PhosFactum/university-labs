all:
	nasm -f elf64 -g -o program.o program.asm -O0
	ld -o program program.o
	./program
