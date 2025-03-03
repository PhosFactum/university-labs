
all:
	gcc -c -g -ggdb -o ctest.o ctest.c
	nasm -f elf64 -F dwarf -g mytest.asm -o mytest.o
	gcc -m64 -o mytest.exe ctest.o mytest.o -g -ggdb -no-pie -z noexecstack
clean:
	rm -f *.o 
