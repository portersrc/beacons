#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sched.h>

#define TIME 1

#define MAX_SIZE 167772160

int random_array1[MAX_SIZE];
int random_array2[MAX_SIZE];
int loop_bound1 = 0, loop_bound2 = 0;

void init_random_array1() {
  srand(0);
  for (int i = 0; i < loop_bound1; i++) {
    random_array1[i * 64 % MAX_SIZE] = rand() % 100; 
  }
}

int sum = 0;
void process_array1() {
  for (int i = 0; i < loop_bound2; i++) {
    // This will ensure that this will be all cache hits.
    sum += random_array1[i % 10];
  }
}

void init_random_array2() {
  srand(0);
  for (int i = 0; i < loop_bound1; i++) {
    random_array2[i * 64 % MAX_SIZE] = rand() % 100; 
  }
}

int main_aux() {
#ifdef TIME
  struct timeval start, end;
  unsigned long time_diff;
  gettimeofday(&start, NULL);
#endif


  init_random_array1();


#ifdef TIME
  gettimeofday(&end, NULL);
  time_diff = (1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec));
  fprintf(stderr, "Time (us): %ld\n", time_diff);
  gettimeofday(&start, NULL);
#endif


  process_array1();


#ifdef TIME
  gettimeofday(&end, NULL);
  time_diff = (1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec));
  fprintf(stderr, "Time (us): %ld\n", time_diff);
  gettimeofday(&start, NULL);
#endif


  init_random_array2();


#ifdef TIME
  gettimeofday(&end, NULL);
  time_diff = (1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec));
  fprintf(stderr, "Time (us): %ld\n", time_diff);
  gettimeofday(&start, NULL);
#endif


  fprintf(stderr, "sched_getcpu(): %d\n", sched_getcpu());
  fprintf(stderr, "The sum is: %d\n", sum);
  return 0;
}

int main(int argc, char **argv) {
  char *argv1 = strtok(argv[1], ":");
  char *argv2 = strtok(NULL, ":");
  loop_bound1 = atoi(argv1);
  loop_bound2 = atoi(argv2);
  return main_aux();
}
