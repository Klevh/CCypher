#!/bin/makefile

debug:debug.o
	gcc $^ -o $@

%.o:%.c
	gcc -c $< -Wall -Wextra -pedantic

clear:
	rm *.o *~
clean: clear
