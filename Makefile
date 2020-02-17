default: main

all: main


main: main.o main1.o
	gcc -w -m32 main.o main1.o -o main

main.o: main.c
	gcc -std=c99 -m32 -Wall -Werror -c main.c

main1.o: main1.asm
	nasm -f macho --prefix _  main1.asm

clean:
	rm -f *.o main