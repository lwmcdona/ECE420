#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>

#include "Lab3IO.h"
#include "timer.h"

int elimination(int num_threads);
void swap_row(double ***A, int k, int idx, int size);

int elimination(int num_threads) {
  double ** A;
  int i,j,k;
  int l, max, idx;
  int rows,cols;
  double temp;
  double start, finished;
  double* x;

  if (Lab3LoadInput(&A, &rows) == 1) { printf("Error in lodaing\n"); return 1;}
  cols = rows + 1;
  x = CreateVec(rows);

  GET_TIME(start);

  // Gaussian
  for (k=0;k<rows-1;k++) {
    for (l=k;l<rows;l++){
      if (l == k) {
        idx = k;
        max = A[l][k];
      }

      if (fabs(A[l][k]) > max ) {
        idx = l;
        max = fabs(A[l][k]);
      }
    }
    if (idx != k) {
      swap_row(&A, k, idx,cols);
    }
    for (i=k+1;i<rows;i++) {
      temp = A[i][k] / A[k][k];
      for (j=k;j<rows+1;j++){
        A[i][j] = A[i][j] - temp * A[k][j];
      }
    }
  }

  // Jordan
  for (k=rows-1; k>0;k--){
    for (i=0;i<k;i++){
      A[i][rows] = A[i][rows] - A[i][k] / A[k][k] * A[k][rows];
      A[i][k] = 0;
    }
  }

  for (k=0; k< rows; ++k)
    x[k] = A[k][rows] / A[k][k];

  GET_TIME(finished);

  Lab3SaveOutput(x,rows,finished-start);
  return 0;
}

void swap_row(double ***A, int k, int idx, int size) {
  int i;
  double temp;

  for (i=0;i<size;i++) {
    temp = (*A)[k][i];
    (*A)[k][i] = (*A)[idx][i];
    (*A)[idx][i] = temp;
  }
}


/*
Main function

*/
int main(int argc, char* argv[])
{
  int num_threads;

  if (argc != 2) {
    printf("Usage: main <number_of_threads>\n");
    return(1);
  }

  num_threads = atoi(argv[1]);

  elimination(num_threads);


  return(0);
}
