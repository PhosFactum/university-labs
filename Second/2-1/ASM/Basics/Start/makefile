all:
	nasm -f elf64 -F dwarf -g mytest.asm 
	gcc -m64 -o mytest mytest.o -g -ggdb -no-pie -z noexecstack
