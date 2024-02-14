#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct FileInfo
{
	int size;
	int len;
} date;

int main (int argc, char* argv[])
{
	int cd;
	int size;
	int len_name = strlen(argv[2])+1;
	struct sockaddr_in addr;
	if ((cd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Error calling socket");
		return __LINE__;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(2021);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if ((-1) == connect(cd, (struct sockaddr *)&addr, sizeof(addr)))
	{
		perror("connect");
		return __LINE__;
	}

	FILE *fd;
	if ((fd = fopen(argv[1], "rb")) == NULL)
	{
		perror("Cannot open file");
		return __LINE__;
	}

	fseek(fd, 0L, SEEK_END);
	size = ftell(fd); //получение размера файла
	rewind(fd);
	
	date.size = size;
	date.len = len_name;
	char *data_file = malloc(size*sizeof(char));

	if ((fread(data_file, sizeof(char), size, fd)) == EOF) {
	
		perror("Cannot read file");
		return __LINE__;
	}

	send(cd, &date, sizeof(date), 0);
	send(cd, argv[2], len_name,  0);
	send(cd, data_file, size, 0);
	
	free(data_file);
	fclose(fd);
	close(cd);
	return 0;
}
