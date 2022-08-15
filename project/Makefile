CC=gcc
DEPS=main.o ppm.o

all: filter_image

filter_image: $(DEPS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $< -o $@
	
.PHONY: clear
clear:
	rm *.o	
