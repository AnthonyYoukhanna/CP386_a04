

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
//constants
int rows = 5;
int columns = 4;


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
	for (int i = 1; i < argc; i++){
		available.avArray[c] = atoi(argv[i]);
		printf("%d ", atoi(argv[i]));
		
		c++;
	}
	printf("\n");

	//initialize Maximum datastruct
	readFile("sample4_in.txt", &max);

	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			printf("%d ", max.mArray[i][j]);
		}
		printf("\n");
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
int resourceReq(){
	//if request[i] <= need[i] then
    //    if request[i] <= available then
    //        available = available - request[i]
    //        allocation[i] = allocation[i] + request[i]
    //        need[i] = need[i] - request[i]
    //    else Thread[i] must wait since resource is not available
    //else deny request 
    
    return 0;

}

void resourceRelease(){

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
// int safety(){
// 	if(){
//         return 0;
//     }

//     else(){
//         return -1;
//     }

// }

// void commandRun(char *argv[]){


// 	//state - * output current state of data structs

// 	//request

// 	//release

// 	//run - implements safe saequence


// }