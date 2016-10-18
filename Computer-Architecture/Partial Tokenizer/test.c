#include <stdio.h>
#include <stdlib.h>

void soomething();

void something(){
char * some;
some[0]='h';
some[1]='b';
some[2]='g';
some[3]='l';
printf("%s\n", some);
}
int main(int argc, char ** argv){

char* chararr;
char random = 'p';

chararr[0]='r';
chararr[1] ='f';
chararr[2] ='g';
chararr[3]= random;
chararr[4] = random;

printf("%s\n", chararr);
something();
}
