all: develop.exe production.exe
	@echo "Done"
develop.exe: main.c dev.c
	@echo "Build develop.exe"
	@gcc -o develop.exe main.c dev.c
production.exe: main.c prod.c
	@echo "Build production.exe"
	@gcc -o production.exe main.c prod.c -lm -Ofast
clean:
	@echo "Clean project"
	@rm -f *.exe
