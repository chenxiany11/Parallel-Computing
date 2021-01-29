#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
//Write a program that prompts the user for an integer value and 
//distributes the value to all of the MPI processes.
int main(int argc, char** argv){
  	MPI_Init(&argc,&argv);
  	int num_procs;
  	int rank;

  	MPI_Comm_size(MPI_COMM_WORLD,&num_procs); 
  	MPI_Comm_rank(MPI_COMM_WORLD,&rank); 
	//Rank 0 should do the prompting and reading
  	if (rank==0){
  		//initialize n with 0
  		int n = 0;
  		while(n>=0){
  			printf("Input an integer: \n");
  			fflush(stdout);
  			scanf("%d", &n);
  			int i;
  			for(i=1; i<num_procs; i++){
  				//use MPI Send to send the data to each worker process in turn
  				MPI_Send(&n,1,MPI_INT,i,0,MPI_COMM_WORLD);
  			}
  		}
  	}else{
  		MPI_Status status;
  		int recv = 0;
  		while(recv>=0){
  			//each worker process should print out its
			//rank and the value it received.
  			MPI_Recv(&recv, 1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
  			printf("Rank: %d Receiced: %d\n", rank, recv);
  			fflush(stdout);
  		}
  	}

	MPI_Finalize();
	return(0);
}