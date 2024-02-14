CC = gcc

all: main 
	@./main 123 inp.txt out.txt
	@./main 123 out.txt out1.txt

main: main.c
	@gcc main.c -o main
	@echo "Compiled"

clean: 
	@rm -fv out.txt out1.txt main
	@echo "Clean project"
