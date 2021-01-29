#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//1
int isprime(int n){
	if(n<2){
		return 0;
	}
	int i;
	for(i=2; i<=sqrt(n); i++){
		if(n%i==0){
			return 0;
		}
	}
	return 1;
}

//2
int isMersenne(int n){
	if(isprime(n)==0){
		return 0;
	}
	int temp = n+1;
	while(temp!=1){
		if(temp%2!=0){
			return 0;
		}
		temp = temp/2;
	}
	return 1;
}

void prime_info(int* ns, int l, int* num_prime, int* primes, int* num_mersenne, int* mersennes){
	int i;
	int j;
	int countp=0;
	int indexp=0;
	int countm = 0;
	int indexm=0;
	for (i=0; i<l; i++){
		if(isprime(ns[i])==1){
			countp++;
			primes[indexp]=ns[i];
			indexp++;
		}
	}
	num_prime[0]=countp;

	for (j=0; j<l; j++){
		if(isMersenne(ns[j])==1){
			countm++;
			mersennes[indexm]=ns[j];
			indexm++;
		}
	}
	num_mersenne[0]=countm;
}

void printArr(int* arr, int size){
	int i;
	printf("[");
	for(i=0; i<size-1; i++){
		printf("%d,", arr[i]);
	}
	printf("%d]\n", arr[i]);
}

void op(int *arr, int size){
	int num_prime[1]; int num_mersenne[1];
	int primes[size];int mersennes[size];
	prime_info(arr,size,num_prime,primes,num_mersenne,mersennes);
	printf("Consider the array ");
	printArr(arr,size);
	printf("There are %d prime elements, they are ", num_prime[0]);
	if(num_prime[0]==0){
		printf("[]\n");
	}else{
		printArr(primes, num_prime[0]);
	}
	printf("There are %d Mersenne prime elements, they are ", num_mersenne[0]);
	if(num_mersenne[0]==0){
		printf("[]\n");
	}else{
		printArr(mersennes, num_mersenne[0]);
	}

}

//testing
int main(int argc, char** argv){
	int i;

	if(strcmp(argv[1],"--list\0")==0){
		int size = argc-2;
		int arr[size];
		
		for(i=0; i<size;i++){
			arr[i]=atoi(argv[i+2]);
		}
		op(arr,size);
		

	}else if(strcmp(argv[1],"--range\0")==0){
		if(argc!=4){
			printf("See usage information\n");
			return 0;
		}
		int l = atoi(argv[2]);
		int r = atoi(argv[3]);
		int size = r-l+1;
		int arr[size];
		int i;
		for (i=0; i<size; i++){
			arr[i]=l+i;
		}
		op(arr,size);
	}else{
		printf("See usage information\n");
		return 0;
	}
	
}