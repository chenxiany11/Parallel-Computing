#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

void my_scatter(int* sendbuf, int sendcount, int* recvbuf, int recvcount, int root){

	int rank;
	int size;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	if(rank==root){
		int i;
		for (i=0;i<size;i++){
			if(i!=root){
				MPI_Send(sendbuf, sendcount, MPI_INT, i, 1,MPI_COMM_WORLD);
			}else{
			//copy thedta into the buffer
				memcpy(recvbuf, sendbuf, sendcount*4);
			}
			sendbuf+=sendcount;
		}
	}else{
		MPI_Recv(recvbuf, recvcount,MPI_INT, root, MPI_ANY_TAG,MPI_COMM_WORLD, &status);
	}

}
