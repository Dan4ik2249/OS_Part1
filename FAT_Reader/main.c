#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
int fd;
uint16_t offset_first_fat;
uint16_t offset_directory;

uint16_t next_cluster(uint16_t cluster)
{
	uint16_t val;
	uint32_t offset = offset_first_fat + (cluster % 2) + (cluster/2)*3;

	lseek(fd, offset, SEEK_SET);
	read(fd, &val, 2);
	
	if ( (cluster % 2) == 0)
	{
		val = val & 0x0fff;
	}
	else
	{
		val = val >> 4;
	}
	return val;
}

uint16_t next_file_record(uint16_t file_record)
{
	uint8_t record[32];
	uint32_t file_size;
	uint32_t offset_size = offset_directory + file_record*0x20;

//	printf("0x%04x", offset);
	lseek(fd, offset_size, SEEK_SET);	
	read(fd, &record, 32);
	
	if (record[0] == 0 || record[0] == 0xe5)
	{
		printf("free record");
		return 0;
	}


	if (record[0xB] == 0x0f) printf("long name\n");
	if (record[0xB] == 0x10) printf("Directory\n");
	if (record[0xB] == 0x20)
	{
		file_size = *(uint32_t*)((record)+0x1C);
		printf("File; File size: 0x%08x\n", file_size);
		printf("First cluster: %d\n", record[0x1A]);
	}
	return file_size;
}

int main(int argc, char* argv[])
{
//	int fd;
	uint16_t sector_size, sector_reserv, fat_size, count_writes;
	uint8_t fats_count;
//	uint16_t offset_first_fat;
//	uint16_t offset_directory;
	uint16_t offset_date;
//	uint8_t record[32];

	if (argc != 2)
	{
		fprintf(stderr, "Use: %s <floppy.img>\n", argv[0]);
		return -1;
	}

	fd = open(argv[1], O_RDONLY);
	if ( (-1) == fd)
	{
		perror("Open image");
			return -2;
	}
	
	lseek(fd, 0xb, SEEK_SET);
	read(fd, &sector_size, 2);
	printf("Sector size: 0x%04X (%u)\n", sector_size, sector_size);
	
	lseek(fd, 0xE, SEEK_SET);
	read(fd, &sector_reserv, 2);
	printf("Reserv sector: 0x%04X (%u)\n", sector_reserv, sector_reserv);
	
	lseek(fd, 0x10, SEEK_SET);
	read(fd, &fats_count, 1);
	printf("FATs count: 0x%02X (%u)\n", fats_count, fats_count);

	lseek(fd, 0x16, SEEK_SET);
	read(fd, &fat_size, 2);
	printf("FAT size: 0x%04X (%u)\n", fat_size, fat_size);

	lseek(fd, 0x11, SEEK_SET);
	read(fd, &count_writes, 2);
	printf("Count writes: 0x%04X (%u)\n", count_writes, count_writes);
	
	offset_first_fat = sector_reserv*sector_size;
	offset_directory = sector_size*sector_reserv + fats_count*fat_size*sector_size;
	offset_date = sector_size*sector_reserv + fats_count*fat_size*sector_size + count_writes*32;
	printf("Offset directory : 0x%04x", offset_directory);
		
	for( uint16_t i = 0; i <= 8; i++)
	{
		uint16_t next = next_cluster(i);
		printf("Next cluster for '0x%03X' is '0x%03X'\n", i, next);
	}
	
//	lseek(fd, 0x2600, SEEK_SET);
//	read(fd, record, 32);

//	printf("Attribute 0x%02x\n", record[0xb]);
//	printf("File size 0x%04x\n", *(uint32_t*)((record) + 0x1C));
	printf("0x%04X\n", offset_date);
	next_file_record(1);

	close(fd);
	return 0;
}
