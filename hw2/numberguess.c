#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
	//it seems right but cant be accepted by the test code
	int low = 1;
	int up = 100;
	int num=50;
	char c ;
	int temp = 0;

	printf("Welcome to the wonderful world of number guessing!\n");
	printf("Think of an integer number between 1 and 100.\n");

	
	while(1){
		
		printf("Is your number %d? (Y/N)\n", num);
		scanf("%c", &c);
		getchar();
		//gets(c);

		while((c!='Y'&&c!= 'y') && (c != 'N' && c != 'n')){
			printf("You didn't enter a proper response.  Please respond Y,y,N, or n\n");
			printf("Is your number %d? (Y/N)\n", num);
			scanf("%c", &c);
			getchar();
			continue;
			
		}

		if(c=='y'||c=='Y'){
			printf("Great, bye!\n");
			exit(0);
		}else{
			if(up==num || low==num){
				temp = 1;
				
			}
			printf("Too bad.\n");
			printf("Is my guess too high (H) or too low (L)?\n");
			scanf("%c", &c);
			getchar();
		
			//gets(c);
			temp = num;
			while((c!='H'&&c!= 'h') && (c != 'L' && c != 'l')){
				printf("You didn't enter a proper response.  Please respond H,h,L, or l\n");
				printf("Is my guess too high (H) or too low (L)?\n");
				scanf("%c", &c);
				getchar();
				continue;
				//gets(c);
			}

			if (c == 'H'||c== 'h' ){

				up = num-1;

				num = (low+up)/2;
				printf("Ok, my guess was too high.\n");
			    if (low==temp){
			    	printf("Liar! You cheat!\n");
					exit(0);
			    }

			}else{
				low = num+1;
				num = (low+up)/2;
				printf("Ok, my guess was too low.\n");
				if (up==temp){
			    	printf("Liar! You cheat!\n");
					exit(0);
			    }
			}	
		}
	}

	
}
