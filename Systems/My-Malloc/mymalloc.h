//importing standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Creating static array that is 5000 "bytes" for the purpose of mimicking malloc
static char myblock[5000];

//Function prototyping
//
char* myMalloc(int size);

void free(char*pointer);



