//Name: thr_atomic.c
#define _OPEN_THREADS
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


double global_sum = 0; // setting the sum of both to 0

/** TODO:
Each thread computes the
sum of n/m quadruple roots. Namely, the first thread (i.e. thread 0) computes the sum of quadruple roots from
1 to n/m, the second thread (i.e. thread 1) computes the sum of the quadruple roots from n/m+1 to 2n/m, etc.
When a thread finishes its computation, it should print its partial sum and atomically add it to a shared global
variable. 
*/
/**
void *thread(void *arg) {
  char *ret;


  //printf("thread() entered with argument '%s' '%s'\n", arg[1], arg[2]);
  if ((ret = (char*) malloc(20)) == NULL) {
    perror("malloc() error");
    exit(2);
  }
  strcpy(ret, "This is a test");
  pthread_exit(ret);
}*/

void * collector(void* arg)
{
    int* a = (int*)arg;
    double quadrupleRoot = .25;
    double result[1];
    result[0] = pow((double)a[0]/(double)a[1], quadrupleRoot);
    printf("m=%d, n=%d, & m/n = %f: so quadruple root of m/n = %f\n", a[0], a[1], (double)a[0]/(double)a[1], result[0]);
    pthread_exit((void*)(result));
}


// to use the Shell in Repl.it command is: ./main "m" "n"
//where m and n are integers
int main(int argc, char *argv[]) {
  printf("The early bird gets the worm!\n");

  /**gets the values m and n from the command line arguments and 
  converts them to two integers, respectively.*/
  int m;
  sscanf(argv[1], "%d", &m);
  int n;
  sscanf(argv[2], "%d", &n);
  printf( "\nYou entered: m = %d, n = %d \n\n", m, n);

  /**TODO: Next, it creates m threads using pthread create() and each thread 
  computes the sum of n/m quadruple roots.*/
  /**
  pthread_t thid;
  void *ret;
  //creates instance of params structure

  if (pthread_create(&thid, NULL, thread, argv) != 0) {
    perror("pthread_create() error");
    exit(1);
  }

  if (pthread_join(thid, &ret) != 0) {
    perror("pthread_create() error");
    exit(3);
  }

  printf("thread exited with '%s'\n", ret);
*/
  int i, mn[2], j;
  mn[0] = m;
  mn[1] = n;
  pthread_t thread_tid[m];
  void* passResult;
  double result;
 // Creates number of threads using m input 
  for(i = 0; i < m; i++) {
      pthread_create(&thread_tid[i], NULL, collector, (void*)(mn));// would it be (void*)&thread_tid)?
      pthread_exit(NULL);
      return(0);
  }
// waiting for the threads to finish
  for (j = 0; j < m; j++ )
  {
    pthread_join(thread_tid[j], NULL);
  }

  for(i = 0; i < m; i++) {
      pthread_join(thread_tid[i], &passResult);
      result = ((double*)passResult)[0];
      printf( "\nThis sh**t works?!: result = %f\n\n",  result);
  }


  return 0;
}

