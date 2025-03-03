all:
	nasm -f elf64 -F dwarf -g ctoasm.asm -o ctoasmA.o
	gcc -c -g -ggdb ctoasm.c -o ctoasmC.o 
	gcc -m64 ctoasmC.o ctoasmA.o -g -ggdb -no-pie -z noexecstack -o program
