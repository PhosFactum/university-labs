all:
	nasm -f elf64 -F dwarf -g hello.asm
	gcc -m64 -o hello hello.o -g -ggdb -no-pie -z noexecstack
