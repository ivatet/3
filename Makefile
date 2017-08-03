all: 3.elf

3.elf: main.c
	gcc -O3 -Wall -Wpedantic main.c -o 3.elf

test: 3.elf
	valgrind --tool=memcheck ./3.elf

clean:
	rm 3.elf
