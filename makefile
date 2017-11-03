all: dirinfo.o
	gcc -o runo dirinfo.o

main.o: dirinfo.c
	gcc -c dirinfo.c

run: all
	./runo
