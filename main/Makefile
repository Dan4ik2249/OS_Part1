CC = gcc

all: clean main.c in.txt out.txt out1.txt
	gcc main.c
	./a.out 123 in.txt out.txt
	./a.out 123 out.txt out1.txt

clean: 
	rm -fv out.txt out1.txt
