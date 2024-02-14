#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t cluster_size = 0;
int fd = -1;
uint8_t *shared_cluster = NULL;
uint64_t MFT;
uint8_t FILE_entry_size;

void open_img(char* name) {
	if( (-1) == (fd = open(name, O_RDONLY)) ) {
		perror(__func__);
		exit(-1);
	}

	uint8_t sector[512];
	if ( 512 != read(fd, sector, 512) ) {
		fprintf(stderr,"Error read boot sector\n");
		exit(-1);
	}

	uint16_t sector_size = *((uint16_t*)(sector + 0xb));
	uint64_t MFT_size = *((uint64_t*)(sector+0x30));
	FILE_entry_size = *((uint8_t*)(sector + 0x40));
	uint8_t cluster_per_sector = sector[0xd];
	cluster_size = ((uint64_t)sector_size) * ((uint64_t)cluster_per_sector);
	MFT = MFT_size*cluster_size;
	if ( NULL == ( shared_cluster = malloc(cluster_size)) ) {
		perror(__func__);
		exit(-1);
	}
}

void read_cluster_in_place(uint64_t num) 
{
	uint64_t offset = num;
//	uint64_t offset = num * cluster_size;
	if ( offset != lseek(fd, offset, SEEK_SET) ) {
		perror(__func__);
		exit(-1);
	}

	if ( cluster_size != read(fd, shared_cluster, cluster_size) ) {
		perror(__func__);
		exit(-1);
	}
}

void read_file_entry(uint64_t num)
{
	uint64_t offset = MFT + num * FILE_entry_size; 
        read_cluster_in_place(offset);
	
	uint8_t count = shared_cluster[0x14];
	uint64_t offset2 = offset + count; 
	
	while 
	
	
}

int main(int argc, char* argv[])
{
	open_img(argv[1]);

//	read_cluster_in_place(0);
//	write(1, shared_cluster, 512);
	
//	read_cluster_in_place(8);
//	write(1, shared_cluster, 16);

	read_file_entry(0);
	write(1, shared_cluster, 512);
	return 0;
}

void __attribute__((destructor)) garbages_collector (void) 
{
	if ( fd > 0) {
		fprintf(stderr,"Close image file\n");
		close(fd);
	}

	if ( NULL != shared_cluster ) {
		fprintf(stderr,"Free shared memory\n");
		free(shared_cluster);
	}
}
