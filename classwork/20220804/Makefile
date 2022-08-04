CC=gcc

main: sll.o main.o
	$(CC) $^ -o $@

%.o: %.c %.h
	$(CC) -c $< -o $@

.PHONY: clear
clear:
	rm *.o

.PHONY: run
run:
	./main
