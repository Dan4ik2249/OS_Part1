#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "sched.h"

static int process_count;
static int *process_time;
int first_test = 2;
static int current_process;
static int active_processes;

int sched_init(void)
{
  return 0;
}

void sched_clean(void)
{
  first_test--;
  active_processes = process_count;
  current_process = 0;
}

int add_proc(void)
{
  return (process_count++);
}

int sched(int time, int cont)
{
  if (!process_time) {
    current_process = process_count;
    if (NULL == (process_time = malloc(sizeof(int) * process_count))) {
      perror("malloc");
      return -1;
    }
    for (int i = 0; i < process_count; ++i) {
      process_time[i] = 0;
    }
  }
  
  if (first_test) {
    if (cont == 0) {
	   current_process--;
    }
    process_time[current_process] += time;
    return current_process;
  }
  else {

  int min_time = process_time[0];
  int min_time_process = 0;
  int max_time = process_time[0];
 
  for (int i = 0; i < process_count; ++i) {
    if (process_time[i] < min_time) {
    	min_time = process_time[i];
	min_time_process = i;
    }
    if (process_time[i] > max_time) {
    	max_time = process_time[i];
    }
  }
  current_process = min_time_process;
  if (cont == 0) {
    current_process = min_time_process;
    process_time[min_time_process] = max_time;
    active_processes--;
    if (!active_processes) {
      return (active_processes == 0) ? (-1) : (current_process);
    }
   }
  }
  return current_process;
}

int sched_fin(void)
{
  return 0;
}
