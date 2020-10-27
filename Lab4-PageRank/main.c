/*
   Second try parallelization
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
    double *r, *r_pre, *contribution, *r_local, *contribution_local;
    int i, j;
    double damp_const;
    int iterationcount = 0;
    FILE *ip;
    double start, end;
    int numprocesses, myrank;
    int blocksize, elementcount;
    int continueLoop = 1;

    int mystart, myend;

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

    blocksize = (int) (nodecount/numprocesses);
    if (blocksize * numprocesses != nodecount) {
        blocksize += 1;
    }
    elementcount = blocksize * numprocesses;
    //printf("Count: %i, Processes: %i, Size: %i", nodecount, numprocesses, blocksize);

    // initialize variables
    r_local = malloc(blocksize * sizeof(double));
    r = malloc(elementcount * sizeof(double));
    r_pre = malloc(elementcount * sizeof(double));
    for ( i = 0; i < nodecount; ++i)
        r[i] = 1.0 / nodecount;

    contribution = malloc(elementcount * sizeof(double));
    contribution_local = malloc(blocksize * sizeof(double));
    for ( i = 0; i < nodecount; ++i)
        contribution[i] = r[i] / nodehead[i].num_out_links * DAMPING_FACTOR;
    damp_const = (1.0 - DAMPING_FACTOR) / nodecount;


    // CORE CALCULATION
    GET_TIME(start);

    do{
        if (myrank == 0) {
          ++iterationcount;
          vec_cp(r, r_pre, nodecount);
        }

        mystart = myrank*blocksize;
        myend = (myrank+1)*blocksize - 1;

        // update the value
        for ( i = mystart; i <= myend && i < nodecount; ++i){
            r_local[i-mystart] = 0;
            for ( j = 0; j < nodehead[i].num_in_links; ++j)
                r_local[i-mystart] += contribution[nodehead[i].inlinks[j]];
            r_local[i-mystart] += damp_const;
        }

        // update and broadcast the contribution
        for ( i=mystart; i <= myend && i<nodecount; ++i){
            contribution_local[i-mystart] = r_local[i-mystart] / nodehead[i].num_out_links * DAMPING_FACTOR;
        }

        MPI_Gather(r_local, blocksize, MPI_DOUBLE, r, blocksize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Allgather(contribution_local, blocksize, MPI_DOUBLE, contribution, blocksize, MPI_DOUBLE, MPI_COMM_WORLD);

        if (myrank == 0) {
            continueLoop = (rel_error(r, r_pre, nodecount) >= EPSILON);
        }
        MPI_Bcast(&continueLoop, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // gather contribution
    }while(continueLoop);
    GET_TIME(end);

    MPI_Finalize();

    if (myrank == 0) {
      printf("Program converged at %d th iteration.\nElapsed time %f.\n", iterationcount, end-start);
      Lab4_saveoutput(r, nodecount, end-start);

      // post processing
      node_destroy(nodehead, nodecount);
      free(contribution);

      free(r); free(r_pre);
      free(r_local);
      free(contribution_local);
    }
    return 0;
}



/*
Main function

*/
int main(int argc, char* argv[])
{
  page_rank();

  return(0);
}
