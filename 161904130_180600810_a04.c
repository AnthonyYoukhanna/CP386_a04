

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

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

//list of commands

char RQ[2];
char RL[2];
char state[1];
char run[3];


typedef struct available
{
	int avArray[4];
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



void readFile(char* fileName, Max *max);
void commandRun(char *c);
int resourceReq(int *tNum, int *r1, int *r2, int *r3, int *r4);
void resourceRelease(int *tNum, int *r1, int *r2, int *r3, int *r4);
int safety();
void printState();

int main(int argc, char *argv[])
{

	if(argc<2)
	{
		printf("Input file name missing...exiting with error code -1\n");
		return -1;
	}


	
	Max max;
	Available available;
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

	//initialize Maximum datastruct
	readFile("sample4_in.txt", &max);
	printf("Maximum resources from file: \n");
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			printf("%d ", max.mArray[i][j]);
		}
		printf("\n");
	}

	//ask for command input
	printf("Enter a command : ");
	//command is string for commands: RQ, RL
	scanf("%s", command);
	//cmd is string for command: *
	strncpy(cmd, command, 1);
	//runcmd is string for command: Run
	strncpy(runcmd, command, 3);
	
	if (strcmp(command, "*") != 0 && strcmp(command, "Run") != 0){
		scanf("%d %d %d %d %d", &threadNum, &r1, &r2, &r3, &r4);
		commandRun(command);
	}
	else if (strcmp(cmd, "*") == 0){
		commandRun(cmd);
	}
	else if(strcmp(runcmd, "Run") == 0){
		commandRun(runcmd);
	}
	

}



void readFile(char* fileName, Max *max)
{
	
    FILE *in = fopen(fileName, "r");

    if(!in)
	{
		printf("Child A: Error in opening input file...exiting with error code -1\n");
	}
	else{
		    const char s[1] = ",";
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
    
    return 0;

}

void resourceRelease(int *tNum, int *r1, int *r2, int *r3, int *r4){

}

//safety algorithm
// 1.let work = available and finish[i] =  false for each resource
// 2.find an index such that both
// 	finish[i] == false
// 	need[i] <= work
// if no such i exists go to step 4
// 3.work = work + allocation[i]
//   finish[i] = true
//   go to step 2
// 4.if finish[i] == true for all i, then system is safe. else state is unsafe.


//checks if resourceReq can be satisfied or denied
int safety(){
	return 0;

}

void printState(){

}

void commandRun(char *c){


	//state - * output current state of data structs
	if (strcmp(c, "*") == 0){
		printState();
		
	}
	//request
	else if (strcmp(c, "RQ") == 0){
		resourceReq(&threadNum, &r1, &r2, &r3, &r4);
		
	}
	//release
	else if (strcmp(c, "RL") == 0){
		resourceRelease(&threadNum, &r1, &r2, &r3, &r4);
		
	}
	//run - implements safe sequence and runs threads
	else if (strcmp(c, "Run") == 0){
		

	}

}