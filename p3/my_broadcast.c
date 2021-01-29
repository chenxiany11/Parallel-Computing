#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

void my_broadcast(int* buffer, int count){
	int rank;
	int size;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	if(rank!=0){

		int tool;
		int index = 0;
		for(tool=1;tool<=rank;tool*=2){
			index++;
		}
		int num = pow(2,index)/2;
		MPI_Recv(buffer, count, MPI_INT,rank-num, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		while(size-2*num>rank){
			MPI_Send(buffer, count, MPI_INT,2*num+rank,1, MPI_COMM_WORLD);
			num = num*2;
		}
	}else{
		int i;
		for(i=1;i<size;i*=2){
			MPI_Send(buffer,count,MPI_INT,i,1,MPI_COMM_WORLD);
		}
	}

	
}