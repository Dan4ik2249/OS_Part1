#include <stdlib.h>
#include <stdio.h>

void main(int argc, char* argv[])
{
	char buffer[80];
	FILE* in = fopen(argv[1], "r");
	while(fscanf(in, "%s79", buffer) == 1)
	printf("%s\n", buffer);
	fclose(in);
}
