/*
  Serial program with MPI
*/

#define LAB4_EXTEND

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "Lab4_IO.h"
#include "timer.h"

#define EPSILON 0.00001
#define DAMPING_FACTOR 0.85

#define THRESHOLD 0.0001

int page_rank();

int page_rank() {
  struct node *nodehead;
  int nodecount;
  double *r, *r_pre, *contribution;
  int i, j;
  double damp_const;
  int iterationcount = 0;
  FILE *ip;
  double start, end;
  int numprocesses, myrank;
  int blocksize, elementcount;

  // Load the data and simple verification
  if ((ip = fopen("data_input_meta","r")) == NULL) {
    printf("Error opening the data_input_meta file.\n");
    return 254;
  }
  fscanf(ip, "%d\n", &nodecount);
  fclose(ip);

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocesses);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

  if (node_init(&nodehead, 0, nodecount)) return 1;

  blocksize = (((int) nodecount/numprocesses) + 1);
  elementcount = blocksize * numprocesses;
  // printf("Count: %i, Processes: %i, Size: %i", nodecount, numprocesses, blocksize);

  // initialize variables
  r = malloc(elementcount * sizeof(double));
  r_pre = malloc(elementcount * sizeof(double));
  for ( i = 0; i < nodecount; ++i)
    r[i] = 1.0 / nodecount;

  contribution = malloc(elementcount * sizeof(double));
  for ( i = 0; i < nodecount; ++i)
    contribution[i] = r[i] / nodehead[i].num_out_links * DAMPING_FACTOR;
  damp_const = (1.0 - DAMPING_FACTOR) / nodecount;


  // CORE CALCULATION
  GET_TIME(start);

  do{
    ++iterationcount;
    vec_cp(r, r_pre, nodecount);



    // update the value
    for ( i = 0; i < nodecount; ++i){
      r[i] = 0;
      for ( j = 0; j < nodehead[i].num_in_links; ++j)
        r[i] += contribution[nodehead[i].inlinks[j]];
      r[i] += damp_const;
    }

    //gather r
    //scatter contribution

    // update and broadcast the contribution
    for ( i=0; i<nodecount; ++i){
      contribution[i] = r[i] / nodehead[i].num_out_links * DAMPING_FACTOR;
    }

    // gather contribution
  }while(rel_error(r, r_pre, nodecount) >= EPSILON);
  GET_TIME(end);

  if (myrank == 0) {

    printf("Program converged at %d th iteration.\nElapsed time %f.\n", iterationcount, end-start);
    Lab4_saveoutput(r, nodecount, end-start);
  }

  MPI_Finalize();

  // post processing
  node_destroy(nodehead, nodecount);
  free(contribution);

  free(r); free(r_pre);
  return(0);
}



/*
 Main function

 */
int main(int argc, char* argv[])
{
  page_rank();

  return(0);
}
