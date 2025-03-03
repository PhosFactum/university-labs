EXERCISES = add sub mul div  # var to collect all execs

all: ${EXERCISES}		     # using this var

add: add.o
	gcc -m64 -g -ggdb -no-pie -z noexecstack -o add add.o
add.o: add.asm
	nasm -f elf64 -F dwarf -g add.asm

sub: sub.o
	gcc -m64 -g -ggdb -no-pie -z noexecstack -o sub sub.o
sub.o: sub.asm
	nasm -f elf64 -F dwarf -g sub.asm

mul: mul.o
	gcc -m64 -g -ggdb -no-pie -z noexecstack -o mul mul.o
mul.o: mul.asm
	nasm -f elf64 -F dwarf -g mul.asm

div: div.o
	gcc -m64 -g -ggdb -no-pie -z noexecstack -o div div.o
div.o: div.asm
	nasm -f elf64 -F dwarf -g div.asm

clean:
	rm -f add.o sub.o mul.o div.o add sub mul div
