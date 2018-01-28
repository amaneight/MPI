/*
*	Author: Aman Sehgal
*	Student ID: 28082419
*	Unit : FIT5139 Advanced Distributed and Parallel Systems 
*	Semester : S1 2017
*	University: Monash University
*
*	Date : 15/5/2017
*
*	Title: Averaging algorithm
*/

#include <stdio.h> //For stdandard input ouput
#include <stdlib.h>
#include "mpi.h" //For MPI related operations
#define rho 50 //Drift rate
#define epsilon 700 //Maximum acceptable drift


//Calculate average
float compute_avg(float current_timestamp,float *all_timestamps, int size,int rank)
{
  float sum = 0.f;
  int i;
  
  //Iterate through timestamps recieved by all processes
  for (i = 0; i < size; i++) {

  	//Check for clocks that are out of sync beyond acceptable limit
  	if(abs(all_timestamps[i]-current_timestamp) <epsilon)
  		//Add value of all the timestamps
    	sum += all_timestamps[i];
  }

  //Return averaged value
  return sum / size;
}

int main(int argc, char **argv){

	//Initialize MPI Execution Environment
	MPI_Init(&argc, &argv);
	
	int size, rank;
	// Size of group with MPI Communicator
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Fetch rank of calling process in MPI Communicator
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/*
	 * Generate offset for clock for demonstrating processors with DRIFTS
	 * As each process here indicates a processor.
	 */

	float rand_offset;
	srand(rank);
	rand_offset = 1+(1/((rand()%10+1)*(2e+6)));

	//Generate a pointer for storing timestamps from all processes
	float *ts_all_process = NULL;
	ts_all_process = malloc(sizeof(float) * size);
	
	//Current timestamp
	float current_timestamp;
	current_timestamp = time()*(rand_offset);
	
	//MPI message call: MPI_Allgather to collect timestamps from all the processes in ts_all_process
	MPI_Allgather(&current_timestamp, 1, MPI_FLOAT, ts_all_process, 1, MPI_FLOAT,MPI_COMM_WORLD);
	
	//Compute average value for all timestamps
	float average_value = compute_avg(current_timestamp,ts_all_process, size,rank);	
	
	//Calulate delta_t
	float delta_t = average_value-current_timestamp;
	printf("\nProcess : %d  delta_t : %.2f\n",rank,delta_t);

	//Calculate updated timestamp for the process
	float updated_timestamp = current_timestamp + delta_t;	
	printf("\nProcess : %d  Updated Timestamp : %.2f\n",rank,updated_timestamp);
	
	//Terminate MPI execution environment
	MPI_Finalize();
	return 0;
}
