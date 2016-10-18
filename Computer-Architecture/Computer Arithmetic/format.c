#include "format.h"


counter *mineCreator(char*koop){
counter *m = malloc(sizeof(counter));
m->binary = malloc(sizeof(koop));
//m-> decimal = malloc(sizeof(koop));
m-> floater = malloc(sizeof(koop));
return m;
}

int twoscompli(counter*  mine){

int strlength;
int decivalue;
//int changed;
strlength = strlen(mine->binary)-1;



if(mine->binary[0] == '1'){
mine->sign='-';}
else if(mine->binary[0] == '0'){
mine->sign='+';}

for( strlength= strlen(mine->binary)-1; strlength > -1; strlength--){

if(mine->binary[strlength] == '1'){
mine->binary[strlength] = '0';
}

else if (mine->binary[strlength] == '0'){
mine->binary[strlength] = '1';}

else{
fprintf(stderr,"ERROR! You entered a non-BINARY number\n");
    exit(0);
}
}

decivalue = bintoint(mine->binary);
decivalue = decivalue +1;
return decivalue;
 

}

int bintoint(char*en){
int counter = strlen(en)-1;
int power=1;
int outcome=0;
while(counter !=-1){
if(en[counter] == '1'){
outcome = outcome + power;
power=power*2;
counter--;
}

else{
power= power*2;
counter--;
continue;
}
}

return outcome;
}

int main(int argc, char** argv){
char* type;
if (argc <3 ){
fprintf(stderr,"ERROR! You did not enter the correct amount of arguments");
    exit(0);}

counter *mine;
mine =mineCreator(argv[1]);
mine->binary = argv[1];
type = argv[2];
if(type[0] == 'i' || type[0] == 'I'){
mine ->decimal = twoscompli(mine); 
mine->decimal= mine->decimal * -1;
printf("%d \n",  mine->decimal);
}

else if( type[0] =='f' || type[0] =='F'){

}
return 0;
}
