all:
	gcc -g -ggdb -c -o main.o main.c 
	nasm -g -f elf64 -F dwarf calc_signed.asm -l calc.lst
	nasm -g -f elf64 -F dwarf calc_unsigned.asm -l calc_unsigned.lst
	gcc -no-pie -no-pie -z noexecstack -o prog main.o calc_signed.o calc_unsigned.o
clean:
	rm -f *.o *.lst prog
