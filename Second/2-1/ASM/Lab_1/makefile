all:
	gcc -g -ggdb -c -o main.o main.c 
	nasm -g -f elf64 -F dwarf calc.asm -l calc.lst
	gcc -no-pie -no-pie -z noexecstack -o prog main.o calc.o 
clean:
	rm -f *.o *.lst prog
