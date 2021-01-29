#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char** argv){
	//initialize set up
  	MPI_Init(&argc,&argv);
  	int num_procs;
  	int rank;
	MPI_Comm_size(MPI_COMM_WORLD,&num_procs); 
  	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  	MPI_Status status;

  	//exit when the input format is incorrect 
  	if(argc!=3){
  		printf("Invalid number of arguments.\n");
    	fflush(stdout);
    	MPI_Finalize();
      	return 0;
  	}
  	//exit when P is not even 
  	if(num_procs%2!=0){
  		printf("Please use an even number of processes\n");
  		fflush(stdout);
  		MPI_Finalize();
      	return 0;
  	}
  	//get host name
  	char name[1000];
  	gethostname(name,1000);

  	//asign the input data 
  	int data = atoi(argv[1]);
  	int trip = atoi(argv[2]);
  	int byte = data*1024*1024;
  	//create an array to store recieved value
	int* arr =  (int*)malloc(byte*4);

	if(rank==0){
		printf("Data Size: %d MB\nNumber of Experiments: %d\n", data, trip);
		printf("Communication Speed Test\n--------\n");
	}
	printf("Rank: %d on machine %s\n", rank, name);

	//send and recieve message between two ranks and calculate the speed 
  	if (rank%2==0){
  		//send
  		int i;
  		double starttime, endtime;
  		starttime = MPI_Wtime();
  		for(i=0;i<trip;i++){
  			//send and recieve from the next rank
  			MPI_Send(arr,byte,MPI_CHAR,rank+1,0,MPI_COMM_WORLD);
        	MPI_Recv(arr,byte,MPI_CHAR,rank+1,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
  		}
  		endtime = MPI_Wtime();
  		double t = data/((endtime-starttime)/trip/2);
  		printf("%d <--> %d Transmission Rate:  %fMB/S\n", rank, rank + 1,t);
  }else{
  		int i;
      	for(i = 0; i < trip; i++){
        	MPI_Recv(arr, byte, MPI_CHAR,rank - 1,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        	MPI_Send(arr, byte, MPI_CHAR, rank - 1, 0, MPI_COMM_WORLD);
      	}
  }
  MPI_Finalize();
  free(arr);
  return 0;
}

