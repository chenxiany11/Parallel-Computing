#include <stdio.h>
#include <stdlib.h>

//1
int countEven(int* arr, int size){
	int i;
	int count=0;
	for(i=0; i<size; i++){
		if(arr[i]%2==0){
			count++;
		}
	}
	return count;
}

//2
double* maximum(double* a, int size){
	double* op = a;
	int i;
	for(i=1; i<size; i++){
		if(a[i]>*op){
			op=a+i;
		}
	}
	return op;
}

//3
int myStrLen(char* s){
	int count = 0;
	while(*s!='\0'){
		count++;
		s++;
	}
	return count;
}

//4
void revString(char* s){
	int len = myStrLen(s);
	int i;
	for(i=0; i<len/2; i++){
		char temp = *(s+i);
		*(s+i)=*(s+len-1-i);
		*(s+len-1-i) = temp;
	}
	
}

//5
void delEven(int* arr, int size){
	int i;
	for(i=0;i<size;i++){
		if(arr[i]%2 == 0){
			arr[i] = (-1);
		}
		
	}
}

int main(int argc, char** argv){
	int size = 10;

	//test countEven
	int i;
	int arr1[size];
	for (i=0; i<size; i++){
		arr1[i]= i+2;
	}
	printf("countEven: %d\n",countEven(arr1,size));

	//test maximum
	double arr2[size];
	for (i=0; i<size; i++){
		arr2[i]= i+2.5;
	}
	printf("maxium: %f\n",*(maximum(arr2,size)));

	//test myStrLen
	char* str = "hello";
	printf("The length of string is %d\n", myStrLen(str));

	//test revString
	//test delEven
}