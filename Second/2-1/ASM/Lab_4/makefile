all:
	nasm -f elf64 -F dwarf -g  program.asm -o program.o
	ld -m elf_x86_64 -O0  -o program program.o 
	./program input.txt #Передача файла в программу
clean:
	rm -rf program.o 
