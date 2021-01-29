#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

void my_allgather(int* sendbuf, int sendcount, int* recvbuf){
	int rank;
	int size;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	//first copy data into the recvbuf
	memcpy(recvbuf+rank*sendcount, sendbuf, 4*sendcount);

	for (int i=1; i<size; i++){
		int temp = (rank+i)%size;
		//create a buffer to receive message
		int* buf = malloc(4*sendcount);
		if(rank!=0){
			//each processor shoul recv and send by the same times
			MPI_Recv(buf, sendcount, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
			MPI_Send(sendbuf, sendcount, MPI_INT, temp, 0, MPI_COMM_WORLD);
		}else{
			//first procossor always send first then recv
			MPI_Send(sendbuf, sendcount, MPI_INT, temp, 0, MPI_COMM_WORLD);
			MPI_Recv(buf, sendcount, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
		}
		//copy the recieved message into recvbuf
		memcpy(recvbuf+status.MPI_SOURCE*sendcount, buf, 4*sendcount);
		free(buf);
	}
}