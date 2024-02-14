#include <malloc.h>
#include <stdio.h>

unsigned int COLS, LINES, COLS2, LINES2,  *A = NULL, *B =NULL, *C = NULL;


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
  COLS = LINES = 8;

  if ( NULL == (A = (int*)malloc(COLS*LINES*sizeof(int)))) {
    perror("alloc for A");
    return __LINE__;
  }

  if ( NULL == (B = (int*)malloc(COLS*LINES*sizeof(int)))) {
    perror("alloc for B");
    return __LINE__;
  }
	
  COLS2 = LINES2 = 6;

  if ( NULL == (C = (int*)malloc(COLS2*LINES2*sizeof(int)))) {
    perror("alloc for C");
    return __LINE__;
  }

  for ( int i = 0 ; i < (COLS*LINES) ; i++ ) {
    A[i] =  3;
    B[i] = 2;
  }
	A[10] = 5;
	A[3] = 2;
	A[15] = 4;
	A[7] = 3;
	A[9] = 7;
  return 0;
}


void print_matrix()
{
  int i, j;

  for ( i = 0 ; i < LINES ; i++ ) {
    printf("|");
     for ( j = 0 ; j < COLS ; j++ ) {
       printf("%3d", A[i*COLS+j]);
     }

     printf(i == (LINES2/2) ?"| = |" :"|   |");
     if (i != 0 && i != LINES - 1)
	     for ( j = 0 ; j < COLS2 ; j++ ) {
		if ((i-1) >= LINES2)	break;
       		printf("%3d", C[(i-1)*COLS2+j]);
     	}
    printf("|\n");
  }
}
