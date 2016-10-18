#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct keeper{
char* binary;
int decimal;
char* floater;
char sign;
};

typedef struct  keeper counter;

int bintoint(char*en);
int twoscompli(counter* mine);


