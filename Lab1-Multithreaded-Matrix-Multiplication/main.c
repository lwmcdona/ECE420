#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>


#include "lab1_IO.h"
#include "timer.h"

int   thread_count;
int** A;
int** B;
int** C;
int n;

void* threadfunc(void* rank) {
  long my_rank = (long) rank;
  int i, j, k;
  int x = floor(my_rank/sqrt(thread_count));
  int y = my_rank % (int)sqrt(thread_count);

  int my_first_row = (n*x)/(int)sqrt(thread_count);
  int my_last_row = (n*(x+1))/(int)sqrt(thread_count);

  int my_first_col = (n*y)/(int)sqrt(thread_count);
  int my_last_col = (n*(y+1))/(int)sqrt(thread_count);

  for (i = my_first_row; i < my_last_row; i++) {
    for (j = my_first_col; j < my_last_col; j++) {
      int sum = 0;
      for (k = 0; k < n; k++) {
        sum += A[i][k]*B[k][j];
      }
      C[i][j] = sum;
    }
  }

  return NULL;
}

void freeArray(int **array, int n) {
  /*
    Frees the memory allocated to a two-dimensional array

    -----
    Input:
    int **array:  Array to free
    int n:        Size of the array to free
  */
  int i;
  for (i = 0; i < n; i++)
  {
    free(array[i]);
  }
  free(array);
}


/*------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
  double     start, end;
  long       thread, thread2;
  pthread_t* thread_handles;
  int        i;

  if (argc != 2) {
    printf("Wrong number of args dude\n");
    exit(1);
  }
  thread_count = atoi(argv[1]);
  if (thread_count <= 0){
    printf("Invalid argument\n");
    exit(1);
  }
  if (sqrt(thread_count)*sqrt(thread_count) != thread_count) {
    printf("Thread count not a square number!!\n");
    exit(1);
  }

  thread_handles = malloc(thread_count*sizeof(pthread_t));


  Lab1_loadinput(&A, &B, &n);

  C = malloc(n * sizeof(int*));

  for (i = 0; i < n; i++)
  {
    C[i] = malloc(n * sizeof(int));
  }
  // Check if n**2 is divisible by thread_count
  if ( (int)(n*n)% thread_count != 0) {
    printf("N*N not divisible by thread_count dummy\n");
    exit(1);
  }

  GET_TIME(start);
  for (thread = 0; thread < thread_count; thread++)
    pthread_create(&thread_handles[thread], NULL,
        threadfunc, (void*) thread);

  for (thread2 = 0; thread2 < thread_count; thread2++)
    pthread_join(thread_handles[thread2], NULL);
  GET_TIME(end);

  Lab1_saveoutput(C, &n, end-start);


  freeArray(A, n);
  freeArray(B, n);
  freeArray(C, n);

  return 0;
}  /* main */
