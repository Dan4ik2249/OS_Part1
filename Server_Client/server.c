#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct FileInfo
{
	int size; //file size
	int len;// name size
} ForFile;

int main(int argc, char* argv[])
{
	int sd, cd;
	struct sockaddr_in addr;
//	char file_name[16];
//	char data[16];
	int msg_name;
	int msg_date;
	int msg_fileInfo;
	ForFile info;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0)
	{
		perror("Error calling socket");
		return __LINE__;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(2021);
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");

	if (bind(sd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("Bind");
		return __LINE__;
	}

	if (listen(sd, 5))
	{
		perror("Listen");
		return __LINE__;
	}

	if ((cd = accept(sd, NULL, NULL)) < 0)
	{
		perror("Accept");
		return __LINE__;
	}
	
	msg_fileInfo = recv(cd, &info, sizeof(info), 0);
	char file_name[info.len];
	char *data = malloc(info.size*sizeof(char));	
	msg_name = recv(cd, file_name, info.len, 0);
	FILE* fd;
	if ((fd = fopen(file_name, "wb")) == NULL)
	{
		perror("Cannot open file");
		return __LINE__;
	}

	if (msg_name > 0)
	{
		msg_date = recv(cd, data, info.size, 0);
		if (msg_date > 0)
			if ((fwrite(data, sizeof(char), info.size, fd)) == EOF) {
				perror("File not write");
				return __LINE__;
			}
	}
	
	free(data);
	fclose(fd);
	close(cd);
	close(sd);
}
