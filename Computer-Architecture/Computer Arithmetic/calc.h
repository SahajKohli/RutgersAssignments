#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>


struct carrier{
int first;
int second;
int final;
char operation;
char finalstate;
char firsttype;
char secondtype;
int sign1;
int sign2;
};

typedef struct carrier Arguments;


Arguments* parser(char** given );
int convertInt(char* en, char type);
int add (int first, int second,int sign1, int sign2);
int subtract(int first, int second,int sign1, int sign2);
int multiply(int first, int second,int sign1, int sign2);
int devide(int first, int second,int sign1, int sign2);
int convertFinalForm(int n, char form);





