all:final.elf

final.elf:1.o 2.o 3.o
	gcc -o final.elf 1.o 2.o 3.o

1.o:1.c myProject.h
	gcc -c 1.c

2.o:2.c myProject.h
	gcc -c 2.c

3.o:3.c myProject.h
	gcc -c 3.c

clean:
	rm final.elf 1.o 2.o 3.o
