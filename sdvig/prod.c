#include <malloc.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>

unsigned int COLS, LINES, *A = NULL, *B =NULL, *C = NULL;

void __attribute__((destructor)) des(){
  if (A != NULL ) {
    free(A);
  }
  if (B != NULL ) {
    free(B);
  }
  if (C != NULL ) {
    free(C);
  }
}
int buid_matrix()
{
  int fd;
  int ret, matrix_size;
  struct stat st;
  
  if ( (-1) == (fd = open("matrix.rnd",O_RDONLY))) {
    perror("open");
    return __LINE__;
  }

  if ((-1) == fstat(fd, &st)) {
    perror("stat");
    close(fd);
    return __LINE__;
  }

  COLS = LINES = (unsigned int)(sqrt(st.st_size / (2 * sizeof(int))));
  printf("COLSxLINES=%ux%u\n", COLS, LINES);

  matrix_size = COLS*LINES*sizeof(int);
  if ( NULL == (A = (int*)malloc(matrix_size))) {
    perror("alloc for A");
    close(fd);
    return __LINE__;
  }
  if ( NULL == (B = (int*)malloc(matrix_size))) {
    perror("alloc for B");
    close(fd);
    return __LINE__;
  }
  if ( NULL == (C = (int*)malloc(matrix_size))) {
    perror("alloc for C");
    close(fd);
    return __LINE__;
  }

  if ( matrix_size != read(fd, A, matrix_size) ) {
    perror("read A");
    close(fd);
    return __LINE__;
  }

  if ( matrix_size != read(fd, B, matrix_size) ) {
    perror("read B");
    close(fd);
    return __LINE__;
  }
  
  close(fd);
  return 0;
}


void print_matrix()
{
}
