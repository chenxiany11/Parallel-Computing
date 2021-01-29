#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <float.h>

#include "goldbach_helpers.c"

int goldbach_partition_calls=0;
int quit = 1;
int quit2 = 2;
//returns 1 if n is prime, 0 otherwise
int isprime(int n){
  if (n<2){
    return 0;
  }
  int i=2;
  while (i*i<=n){
    if (n%i==0){
      return 0;
    }
    i++;
  }
  return 1;
}



//Attempts to calculate a Golbach partition of n.
//Returns a Goldbach partition that includes the smallest possible prime.
//i.e., both 3/7 and 5/5 are partitions of 10.  3/7 is returned because 3 is the smallest of 3,5,7.
//Returns 1 on success, in this case a and b hold the partition
//Returns 2 if n<=2, or if n is odd
//Returns 3 if you have disproved Golbach's conjecture. 
int goldbach_partition(int n, int* a, int* b){
  goldbach_partition_calls++;
  int exit_code=2;
  if (n<=2 || (n % 2 ==1)){
    return exit_code;
  }

  exit_code=3;

  int i;
  for (i=2;i<=n/2;i++){
    if (isprime(i) && isprime(n-i)){
      *a=i; *b=n-i;
      exit_code=1;
      return exit_code;
    }
  }

  return exit_code;

}

int min(int a, int b){
  return a<b ? a:b;
}


int main(int argc, char** argv){

  MPI_Init(&argc,&argv);

  int rank;
  int size;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  options opt;
  parse_options(argc,argv,&opt);
  int* pool= malloc(4*opt.chunksize);
  MPI_Status status;

  //The command line options have now been parsed properly.
  //They are held in the members of opt.
  //The options you care about are:
  //opt.print_results  -- 0 if you should not print out the partitions you find, 1 if you should
  //opt.to_partition   -- the list of numbers that you should find partitions for
  //opt.num_to_partition -- the length of the list above
  //opt.chunksize -- the control for the "chunksize" of a work assignment.  If the chunksize is n, then processors get assigned to partition n consecutive numbers from the to_partition list as part of 1 assignement. 
  if (rank==0){
    //root
    int i = 0;
    //sending stuff to each processors
    while(i<opt.num_to_partition && i/opt.chunksize+1 < size){
       if(i+opt.chunksize<opt.num_to_partition){
        MPI_Send(opt.to_partition+i,opt.chunksize,MPI_INT,i/opt.chunksize+1,opt.chunksize,MPI_COMM_WORLD);
        i+=opt.chunksize;
       }else{
        MPI_Send(opt.to_partition+i,opt.num_to_partition-i,MPI_INT,i/opt.chunksize+1,opt.num_to_partition-i,MPI_COMM_WORLD);
        i+=opt.chunksize;
      }
    }
    //still have chunks to handle
    while(i<opt.num_to_partition){
      //recieve result 
      MPI_Recv(pool,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
      int diff= opt.num_to_partition-opt.chunksize;
      if(i < diff){
        MPI_Send(opt.to_partition+i,opt.chunksize,MPI_INT,status.MPI_SOURCE,opt.chunksize,MPI_COMM_WORLD);
        i+=opt.chunksize;
      }else{
        MPI_Send(opt.to_partition+i,opt.num_to_partition-i,MPI_INT,status.MPI_SOURCE,opt.num_to_partition-i,MPI_COMM_WORLD);
        i+=opt.chunksize;
      }
    }
    //send done message
    for(i=1;i<size;i++){
      MPI_Send(pool,1,MPI_INT,i,0,MPI_COMM_WORLD);
    }
    
  }else{
    //worker: print out partitions if any
    int result;
    int large, small;
    int i;
    while(1){
      MPI_Recv(pool,opt.chunksize,MPI_INT,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
      if(status.MPI_TAG ==0){
        break;
      }
      for(i=0;i<status.MPI_TAG;i++){
        result = goldbach_partition(pool[i],&small,&large);
        if(opt.print_results && result == 1){
          printf("%d: %d/%d\n", pool[i],small,large);
        }
        if(opt.print_results == 3){
          printf("Find Counter Example!!!");
        }
      }
      //done the work
      MPI_Send(&result,1,MPI_INT,0,0,MPI_COMM_WORLD);

    }
  }
  free(pool);
  MPI_Finalize();
  return 0;
}

