# this should work but it doesn't??
# Look at Makefile from task 1

CC=gcc
MAIN_DEFS=-DCOUNT=10 -DMIN=-10 -DMAX=10

.PHONY: all
all: program 

program: main.o comparators.o
	$(CC) $^ -o $@

main.i: main.c
	$(CC) -E $< $(MAIN_DEFS) -o $@

%.i: %.c %.h
	$(CC) -E $< -o $@

%.S: %.i
	$(CC) -S $< -o $@

%.o: %.S
	$(CC) -c $< -o $@

.PHONY: clear
clear:
	rm *.i *.S *.o
