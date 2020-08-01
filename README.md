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

Error from incorrect input of request command will hint that either

    - the thread does not exist
    - the thread requesting does not have enough resources inputted into the command
    - the thread request would be unsafe

## Tests

Possible Test:



## Code Example

## Authors

## Credits

## License
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software, either in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this software dedicate any and all copyright interest in the software to the public domain. We make this dedication for the benefit of the public at large and to the detriment of our heirs and successors. We intend this dedication to be an overt act of relinquishment in perpetuity of all present and future rights to this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
