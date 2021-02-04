#include <stdio.h>

//Name: thr_atomic.c

int main(int argc, char *argv[]) {
  printf("The early bird gets the worm!\n");
  int m;
  sscanf(argv[1], "%d", &m);
  int n;
  sscanf(argv[2], "%d", &n);




  printf( "\nYou entered: m = %d, n = %d ", m, n);

  return 0;
}