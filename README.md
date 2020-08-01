# CP386_a04
Assignment repository for Operating System assignment 4
## Motivation
Completion of Assignment 4
## Installations
Download the file from the repository

Open on Linux CMD line

Use Makefile command "make" for compilation and/or "make warnings_OK"

Run on linux using "./Assignment X X X X" 

  - X's will be the max resource integer values that the user will input


## Screenshots
![Screenshot1](/pics/first.png "Program Start")

![Screenshot2](/pics/second.png "RQ, and * Example")

![Screenshot3](/pics/third.png "RL and *")

![Screenshot4](/pics/fourth.png "Run command Part 1")

![Screenshot5](/pics/fifth.png "Run command Part 2")

## Individial Contribution
```c
int main(int argc, char *argv[]); //Franchesco/Anthony
void readFile(char* fileName, Max *max); //Franchesco
void commandRun(char *c); //Franchesco
int resourceReq(int *tNum, int *r1, int *r2, int *r3, int *r4); //Franchesco/Anthony
int resourceRelease(int *tNum, int *r1, int *r2, int *r3, int *r4); //Anthony
void printState(); //Franchesco
void fillAlloc(); //Franchesco
void* threadRun(void* t); //Anthony
void createSafe(); //Anthony
void fillNeed(); //Franchesco
```
## Features

## Tests

## Code Example

## Authors

## Credits

## License
