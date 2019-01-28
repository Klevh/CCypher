#!/bin/makefile

OFLAG = 
CFLAG =-Wall -Wextra -ansi -pedantic

nothing:main.o file.o crypt.o
	gcc $^ -o $@ $(OFLAG)

%.o:%.c
	gcc -c $< $(CFLAG)

clean:
	rm *.o *~
clear: clean
