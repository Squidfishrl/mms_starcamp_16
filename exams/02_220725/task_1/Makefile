CC=gcc
MAIN_DEFS=-DCOUNT=10 -DMIN=-10 -DMAX=10

.PHONY: all
all:program 

program: main.o comparators.o
	$(CC) $^ -o $@

main.o: main.c
	$(CC) -c $< $(MAIN_DEFS) -o $@

%.o: %.c %.h
	$(CC) -c $< -o $@

.PHONY: clear
clear:
	rm *.o
