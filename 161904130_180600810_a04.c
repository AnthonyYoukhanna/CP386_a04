/*
CP386 Assignment 4
Wilfrid Laurier University

Franchesco Livado
Student ID: 161904130
Github: FranchescoLivado

Anthony Youkhanna
Student ID: 180600810
Github: AnthonyYoukhanna

https://github.com/AnthonyYoukhanna/CP386_a04
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

//constants
int rows = 5;
int columns = 4;
char command[100];
char cmd[2];
char runcmd[3];
int threadNum;
int r1;
int r2;
int r3;
int r4;	
int safe[5];
//list of commands

char RQ[2];
char RL[2];
char state[1];
char run[3];


typedef struct available
{
	int avArray[4];
	int new[4];
} Available;

typedef struct maximum
{	
	int mArray[5][4];
} Max;

typedef struct allocated
{
	int allocArray[5][4];
} Alloc;

typedef struct need{
	int needArray[5][4];
} Need;

typedef struct thread{
    int numOfReq;
    int tNum;
	int safe;
    //pthread_t handle;
} Threads;

void readFile(char* fileName, Max *max);
void commandRun(char *c);
int resourceReq(int *tNum, int *r1, int *r2, int *r3, int *r4);
int resourceRelease(int *tNum, int *r1, int *r2, int *r3, int *r4);
void printState();
void fillAlloc();
void* threadRun(void* t);
void createSafe();
void fillNeed();


//inits of structs
Threads* threads;
Max max;
Available available;
Alloc allocated;
Need need;

int main(int argc, char *argv[])
{

	if(argc<2)
	{
		printf("Input file name missing...exiting with error code -1\n");
		return -1;
	}

    threads = (Threads*) malloc(sizeof(Threads)*rows);
	
	
	//initialize Available datastruct
	int c = 0;
	printf("Number of Customers: %d \n", rows);
	printf("Currently Available resources: ");
	for (int i = 1; i < argc; i++){
		available.avArray[c] = atoi(argv[i]);

		printf("%d ", atoi(argv[i]));
		
		c++;
	}
	printf("\n");

	//initialize Maximum datastruct and thread attributes
	readFile("sample4_in.txt", &max);
	printf("Maximum resources from file: \n");
	for (int i = 0; i < rows; i++){
        threads[i].tNum = i;
        threads[i].numOfReq = 0;
		threads[i].safe = 0;
		for (int j = 0; j < columns; j++){
			printf("%d ", max.mArray[i][j]);
		}
		printf("\n");
	}

	//ask for command input
	printf("Enter a command : ");
	//command is string for commands: RQ, RL
	scanf("%s", command);
	
	while (strcmp(command, "Run") != 0){
		//cmd is string for command: *
		strncpy(cmd, command, 1);
		

		if (strcmp(command, "*") != 0 && strcmp(command, "Run") != 0){
			scanf("%d %d %d %d %d", &threadNum, &r1, &r2, &r3, &r4);
			printf("command entered\n");
			commandRun(command);
			
		}
		else if (strcmp(cmd, "*") == 0){
			commandRun(cmd);
		}

		printf("Enter a command : ");
		scanf("%s", command);
		//runcmd is string for command: Run
		strncpy(runcmd, command, 3);
	}

	createSafe();
	commandRun(runcmd);
	
	return 0;
}



void readFile(char* fileName, Max *max)
{
	
    FILE *in = fopen(fileName, "r");

    if(!in)
	{
		printf("Child A: Error in opening input file...exiting with error code -1\n");
	}
	else{
		//const char s[1] = ",";
		char line[100];
		char *token;
		int col;
		int row;
		row = 0;
		while(!feof(in))
		{
			fgets(line, sizeof(line), in);
			col = 0;
			token = strtok(line, ",");
			
			while(token != NULL){

				max->mArray[row][col] = atoi(token);
				col++;
				token = strtok(NULL,",");	
				
			}
			row++;
		}
	}
}



//fills Allocation
int resourceReq(int *tNum, int *r1, int *r2, int *r3, int *r4){
    //check if thread has been already requested
    if (threads[*tNum].numOfReq == 0){
        //check if available <= (max - request) AKA Safety algorithm or if (max - request) is negative
        for(int i = 0; i < columns; i++){
		
            if ((i == 0 && ((max.mArray[*tNum][i] - *r1) <= -1)) || (available.avArray[i] - *r1) <= 0){// (max.mArray[*tNum][i] - *r1) > available.avArray[i]) || 
                //printf("i: %d \n(max.mArray[*tNum][i] - *r1): %d - %d \n", i, max.mArray[*tNum][i], *r1);
				
				return -1;					
            }
            if ((i == 1 && ((max.mArray[*tNum][i] - *r2) <= -1)) || (available.avArray[i] - *r2) <= 0){//(max.mArray[*tNum][i] - *r2) > available.avArray[i] || 
                //printf("i: %d \n(max.mArray[*tNum][i] - *r2): %d - %d \n", i, max.mArray[*tNum][i], *r2);
				
				return -1;				
            }
            if ((i== 2 && ((max.mArray[*tNum][i] - *r3) <= -1)) || (available.avArray[i] - *r3) <= 0){ //(max.mArray[*tNum][i] - *r3) > available.avArray[i] || 
				//printf("i: %d \n(max.mArray[*tNum][i] - *r3): %d - %d \n", i, max.mArray[*tNum][i], *r3);
				
				return -1;
            }
            if ((i == 3 && ((max.mArray[*tNum][i] - *r4) <= -1)) || (available.avArray[i] - *r4) <= 0){ //(max.mArray[*tNum][i] - *r4) > available.avArray[i] ||
                //printf("i: %d \n(max.mArray[*tNum][i] - *r4): %d - %d \n", i, max.mArray[*tNum][i], *r4);
				
				return -1;
            }
        }
		for (int i = 0; i < columns; i++){
			if (i == 0){
				available.avArray[i] = available.avArray[i] - *r1;
			}
			if (i == 1){
				available.avArray[i] = available.avArray[i] - *r2;
			}
			if (i == 2){
				available.avArray[i] = available.avArray[i] - *r3;
			}
			if (i == 3){
				available.avArray[i] = available.avArray[i] - *r4;
			}
		}
		
		
		threads[*tNum].numOfReq ++;
        return 0;
    }
    else{
		
        return -1;
    }

}

void fillNeed(){
	for (int j = 0; j < rows; j++){

		for (int i = 0; i < columns; i++){

			need.needArray[j][i] = max.mArray[j][i] - allocated.allocArray[j][i];
			
		}
		
	}
	
}

int resourceRelease(int *tNum, int *r1, int *r2, int *r3, int *r4){
	if (threads[*tNum].numOfReq > 0){
        for(int i = 0; i < columns; i++){
			//checks if there a resources available to release
            if (i == 0 && ((allocated.allocArray[*tNum][i] - *r1) <= -1)){
				
				return -1;					
            }
            if (i == 1 && ((allocated.allocArray[*tNum][i] - *r2) <= -1)){
				
				return -1;				
            }
            if (i== 2 && ((allocated.allocArray[*tNum][i] - *r3) <= -1)){ 
				
				return -1;
            }
            if (i == 3 && ((allocated.allocArray[*tNum][i] - *r4) <= -1)){ 
				
				return -1;
            }
        }
		//adds resources back to available and removes resources from the allocated
		for (int i = 0; i < columns; i++){
			if (i == 0){
				available.avArray[i] = available.avArray[i] + *r1;
				allocated.allocArray[*tNum][i] = allocated.allocArray[*tNum][i] - *r1;
			}
			if (i == 1){
				available.avArray[i] = available.avArray[i] + *r2;
				allocated.allocArray[*tNum][i] = allocated.allocArray[*tNum][i] - *r2;

			}
			if (i == 2){
				available.avArray[i] = available.avArray[i] + *r3;
				allocated.allocArray[*tNum][i] = allocated.allocArray[*tNum][i] - *r3;
			}
			if (i == 3){
				available.avArray[i] = available.avArray[i] + *r4;
				allocated.allocArray[*tNum][i] = allocated.allocArray[*tNum][i] - *r4;
			}
		}

		threads[*tNum].numOfReq --;
        return 0;
    }
    else{
		
        return -1;
    }

}


void printState(){

	printf("Maximum: \n");
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			printf("%d ", max.mArray[i][j]);
		}
		printf("\n");
	}
	printf("\nAvailable: \n");
	for (int i = 0; i < columns; i++){
		printf("%d ", available.avArray[i]);
	}
	printf("\n");
	printf("\nAllocation: \n");
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			printf("%d ", allocated.allocArray[i][j]);
		}
		printf("\n");
	}
	printf("\nNeed: \n");
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			printf("%d ", need.needArray[i][j]);
		}
		printf("\n");
	}

}

void fillAlloc(){
    printf("Allocated array @thread %d: ", threadNum);
    for (int i = 0; i < columns; i++){
        if (i == 0){
            allocated.allocArray[threadNum][i] = r1;
            printf("%d ",allocated.allocArray[threadNum][i]);
        }
        if (i == 1){
            allocated.allocArray[threadNum][i] = r2;
            printf("%d ",allocated.allocArray[threadNum][i]);
        }
        if (i == 2){
            allocated.allocArray[threadNum][i] = r3;
            printf("%d ",allocated.allocArray[threadNum][i]);
        }
        if (i == 3){
            allocated.allocArray[threadNum][i] = r4;
            printf("%d ",allocated.allocArray[threadNum][i]);
        }
    }
}

void commandRun(char *c){

	int b;
	//state - * output current state of data structs
	if (strcmp(c, "*") == 0){
		
		printState();
		
	}
	//request
	else if (strcmp(c, "RQ") == 0){
		b = resourceReq(&threadNum, &r1, &r2, &r3, &r4);
		if (b == 0){
            //fill alloc array then print
            fillAlloc();
			fillNeed();
            printf("Request satisfied \n");
        }
        else{
            printf("Request denied for one of the following reasons:\n	state would be unsafe\n	thread has already been allocated resources\n	thread does not exist\n");
        }
	}
	//release
	else if (strcmp(c, "RL") == 0){
		b = resourceRelease(&threadNum, &r1, &r2, &r3, &r4);
		if (b == 0){
            printf("Request satisfied \n");
        }
        else{
            printf("Request denied for one of the following reasons:\n	state would be unsafe\n	not enough resources\n	thread does not exist\n");
        }
	}
	//run - implements safe sequence and runs threads
	else if (strcmp(c, "Run") == 0){
		int bool = 0;
		int i=0;
		while(i < rows)//put a suitable condition here to run your program
			{
				int tnum = safe[i];
				pthread_attr_t attr;
				pthread_t tid = threads[tnum].tNum;
				pthread_attr_init(&attr);
				bool = pthread_create(&tid, &attr, threadRun, &threads[tnum]);
				//sleep(5);
				pthread_join(tid, NULL);

				if (bool == 0){
					i++;
				}
				//write suitable code here to run the threads
			}

	}

}

void* threadRun(void* t){

	int tid = ((Threads*)t)->tNum;
	printf("--> Customer/Thread %d \n", tid);
	printf("	Allocated resources:	");
	for (int j = 0; j < columns; j++)
	{
		printf("%d ", allocated.allocArray[tid][j]);
	}
		
	printf("\n	Needed:		");
	for (int j = 0; j < columns; j++)
	{
		printf("%d ", need.needArray[tid][j]);
	}	
	
	printf("\n	Available:	");
	for (int j = 0; j < columns; j++)
	{
		printf("%d ", available.avArray[j]);
	}

	printf("\n	Thread has started \n");
	printf("	Thread has finished \n");
	printf("	Thread is releasing resources \n");

	printf("	New Available: ");



	for (int j = 0; j < columns; j++)
	{
		available.avArray[j] = available.avArray[j] + allocated.allocArray[tid][j];
	}




	for (int j = 0; j < columns; j++)
	{
		printf("%d ", available.avArray[j]);
	}
	printf("\n");
	pthread_exit(0);
}

void createSafe(){
	//need <= work then work = work + allocation and add to safe sequence
	for (int i = 0; i < columns; i++)
	{
		available.new[i] =  available.avArray[i];
	}
	
	int added = 0;
	int check = 0;
	while (added < rows)
	{
		for (int i = 0; i < rows; i++)
		{
			if (threads[i].safe == 0)
			{
				for (int j = 0; j < columns; j++)
				{
					if (need.needArray[i][j] <= available.new[j])
					{
						check = 1;
					}else
					{
						check = 0;
						break;
					}
				}
			}	
			if (check == 1)
			{
				printf("thread: %d", threads[i].tNum);
				threads[i].safe = 1;
				safe[added]= threads[i].tNum;
				added++;

				for (int j = 0; j < columns; j++)
				{
					available.new[j] = available.new[j] + allocated.allocArray[i][j];
				}	
			}
			check = 0;
		}
	}
	printf("\n Safe sequence is: <");
	for (int i = 0; i < 5; i++)
	{
		printf(" %d", safe[i]);
	}
	printf(" >\n");
	


}