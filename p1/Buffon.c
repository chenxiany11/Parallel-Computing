#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>
#include<math.h>
#include<unistd.h>

#define rootprint(...) rank==0 ? printf(__VA_ARGS__):0 ; fflush(stdout);


int crosses_line_calls = 0;

int crosses_line(double y_end, double theta){
  crosses_line_calls++;
  if (y_end+sin(theta)>1){
    return(1);
  }
  else{
    return(0);
  }

}  

int main(int argc, char** argv){
  MPI_Init(&argc,&argv);

  int rank;
  int numprocs;
  int i;
  int trial;
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

  if (argc<2){
    rootprint("Usage: %s T\n",argv[0]);
    rootprint("where T is the number of trials on each processor.\n");
    MPI_Finalize();
    return(MPI_SUCCESS);
  }


  //You fill in this part. 

  trial = atoi(argv[1]);
  int seed = time(NULL);
  int sol = 0;
  srand(seed + 100*rank);
  for(i = 0; i < trial; i++){
      double randomy = 1.00 * rand() / RAND_MAX;
      double y = (double) rand() / RAND_MAX;
      double rangle = y * 2 * acos(-1);
      sol += crosses_line(randomy, rangle);    
  }

  double rate, pi;
  rate = 1.0 * sol / trial;
  pi = 1.00 / rate;
  
  if(rank == 0){
      MPI_Status status;
      double temp;
      for(i = 1; i < numprocs; i++){
          MPI_Recv(&temp, 1, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
          pi += temp;
      }
      double estimatep = pi / numprocs;
      printf("%f", estimatep);
  }else{
      MPI_Send(&pi, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }

  
  MPI_Finalize();
  return(MPI_SUCCESS);
}