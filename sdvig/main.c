#include <stdio.h>
#include <pthread.h>
#include <time.h>

extern unsigned int COLS, LINES, *A, *B, *C;
int buid_matrix(void);
void print_matrix(void);

void* func(void* count)
{
	int* n = (int*)count;
	int sum = 0;
	int pass, two_pass;
	for(int p = 0; p < (LINES - 2)/2; p++){

		two_pass = (2*p+*n)*(LINES - 2);
		pass = (2*p+*n)*LINES;
		
		for (int k = 0; k < (LINES - 2); k++){
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++) {
				sum += A[j+i*LINES+k+pass];
				}
			}
			C[k+two_pass] = sum;
			sum = 0;
		}
	}
}

int main(int argc, char *argv[])
{
	pthread_t pid;
	void* ret;
	int i;
 	clock_t begin, end1, end2;
	if (buid_matrix()) {
		return -1;
	}

	begin = clock();
	int n = 1;
	pthread_create(&pid, NULL, func, (void*)&n);
	int k = 0;
	func((void*)&k);
	pthread_join(pid, &ret);
	
	end1 = clock() - begin;
	printf("work with threads: %ld\n", end1);
	

	begin = clock();
	func((void*)&n);
	func((void*)&k);
	end2 = clock() - begin;
	printf("work without threads: %ld\n", end2);
/*
  for(int i = 0; i < (LINES - 2)/2; i++){
	  int count = LINES - 2;
	  opts.two_pass = (2*i+1)*count;
	  opts.pass = (2*i+1)*LINES;
	  func(opts.pass, opts.two_pass);
  } 
*/
  print_matrix();
  return 0;
}

