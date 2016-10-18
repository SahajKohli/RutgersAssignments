#include <stdlib.h>
#include "calc.h"

Arguments* parser(char** given ){
Arguments *Curr = malloc(sizeof(Arguments));
//Set the Sign of both arguments to positive
Curr->sign1=0;
Curr->sign2=0;
//where argv[1] : the operation
Curr->operation = given[1][0];
if(given[1][0] != '+' && given[1][0] != '-' && given[1][0] != 'x' && given[1][0] != '/' ){
fprintf(stderr,"ERROR!! You did not enter the Correct Opertation type\n");
    exit(0);
}


//where argv[2][0]:the first given and type
Curr->firsttype = given[2][0];
if(given[2][0]== '-'){
Curr->firsttype = given[2][1];
Curr->sign1 = 1;
if(given[2][1] != 'b'&& given[2][1] != 'B'&& given[2][1] != 'd' && given[2][1] != 'D'&& given[2][1] != 'o'&& given[2][1] != 'O'&& given[2][1] != 'x'&& given[2][1] != 'X'){
fprintf(stderr,"ERROR!! You did not enter the Correct Charcther type\n");
    exit(0);
}

}
else if(Curr->sign1 != 1 && given[2][0] != 'b'&& given[2][0] != 'B'&& given[2][0] != 'd' && given[2][0] != 'D'&& given[2][0] != 'o'&& given[2][0] != 'O'&& given[2][0] != 'x'&& given[2][0] != 'X'){
fprintf(stderr,"ERROR!! You did not enter the Correct Charcther type\n");
    exit(0);
}


//where argv[2]: All the of the first argument:
char* temp = given[2];
temp = temp+1;
if(Curr->sign1 == 1){
temp = temp+1;}
//printf("temp %s\n ", temp);
Curr-> first = convertInt(temp, Curr->firsttype);
//line below used for debugging and checking converted values
//printf("Converted to %d\n", Curr->first);


//////////second arg/////////////



//where argv[3][0]:the second given and type
Curr->secondtype = given[3][0];
 if(given[3][0]== '-'){
Curr->secondtype = given[3][1];
Curr->sign2 = 1;
if(given[3][1] != 'b'&& given[3][1] != 'B'&& given[3][1] != 'd' && given[3][1] != 'D'&& given[3][1] != 'o'&& given[3][1] != 'O'&& given[3][1] != 'x'&& given[3][1] != 'X'){ fprintf(stderr,"ERROR!!33 You did not enter the Correct Chacther type\n ");
   exit(0);}

}
else if (Curr->sign2 != 1 && given[3][0] != 'b'&& given[3][0] != 'B'&& given[3][0] != 'd' && given[3][0] != 'D'&& given[3][0] != 'o'&& given[3][0] != 'O'&& given[3][0] != 'x'&& given[3][0] != 'X'){ fprintf(stderr,"ERROR!!22 You did not enter the Correct Chacther type\n ");
   exit(0);}


//where argv[3]: All of the second argument
char* temp2 = given[3];
temp2 = temp2+1;
if(Curr->sign2 == 1){
temp2 = temp2+1;
}
//printf("temp %s\n ", temp2);
Curr-> second = convertInt(temp2, Curr->secondtype);
//line below used for debugging and checking converted values
//printf("Converted to %d\n", Curr->second);




//where argv[4]:the final operant
Curr-> finalstate= given[4][0];
if(given[4][0] != 'b' && given[4][0] != 'B' && given[4][0]!='x' && given[4][0]!='X' && given[4][0] != 'o'&& given[4][0] != 'O' && given[4][0]!= 'd' && given[4][0]!='D'){
fprintf(stderr,"ERROR!! You did not enter the Correct Final form type\n");
    exit(0);
}


return Curr;
}

int convertInt(char* en, char type){

//Given is Decimal
if(type == 'd' || type =='D'){
int counter = strlen(en)-1;
int power =1;
int outcome =0;
while(counter != -1){
//printf("What is outcome %d\n", outcome);
if(en[counter]=='1'){
outcome =outcome+ (1*power);
power = power *10;
counter--;
}
else if( en[counter] == '2'){
outcome = outcome + (2*power);
power = power*10;
counter--;
}

else if( en[counter] == '3'){
outcome = outcome + (3*power);
power = power*10;
counter--;
}

else if( en[counter] == '4'){
outcome = outcome + (4*power);
power = power*10;
counter--;
}

else if( en[counter] == '5'){
outcome = outcome + (5*power);
power = power*10;
counter--;
}

else if( en[counter] == '6'){
outcome = outcome + (6*power);
power = power*10;
counter--;
}

else if( en[counter] == '7'){
outcome = outcome + (7*power);
power = power*10;
counter--;
}
else if( en[counter] == '8'){
outcome = outcome + (8*power);
power = power*10;
counter--;
}

else if( en[counter] == '9'){
outcome = outcome + (9*power);
power = power*10;
counter--;
}
else if( en[counter] == '0'){
outcome = outcome + (0*power);
power = power*10;
counter--;
}
else{
printf("ERROR!! The Argument you entered is flawed, The Charcther: %c - IS NOT A DECIMAL\n", en[counter]);
exit(0);
} 
}
return outcome;
}


//Given is Binary
else if( type == 'b' || type == 'B'){

int counter = strlen(en)-1;
int power=1;
int outcome=0;
while(counter !=-1){
if(en[counter] == '1'){
outcome = outcome + power;
power=power*2;
counter--;
}

else if (en[counter] == '0'){
power= power*2;
counter--;
continue;
}

else{
    fprintf(stderr,"ERROR! You entered a non-binary number in a binary string");
    exit(0);
}


}
return outcome;
printf("Should not be here %d \n", outcome);
}


//Given is HexaDecimal
else if( type == 'x' || type == 'X'){

int counter = strlen(en)-1;
int power =1;
int outcome =0;
while(counter != -1){

 if( en[counter] == '0'){
outcome = outcome + (0*power);
power = power*16;
counter--;
}

else if( en[counter] == '1'){
outcome = outcome + (1*power);
power = power*16;
counter--;
}

else  if( en[counter] == '2'){
outcome = outcome + (2*power);
power = power*16;
counter--;
}

else  if( en[counter] == '3'){
outcome = outcome + (3*power);
power = power*16;
counter--;
}

else  if( en[counter] == '4'){
outcome = outcome + (4*power);
power = power*16;
counter--;
}

else  if( en[counter] == '5'){
outcome = outcome + (5*power);
power = power*16;
counter--;
}

else  if( en[counter] == '6'){
outcome = outcome + (6*power);
power = power*16;
counter--;
}

else  if( en[counter] == '7'){
outcome = outcome + (7*power);
power = power*16;
counter--;
}
else  if( en[counter] == '8'){
outcome = outcome + (8*power);
power = power*16;
counter--;
}

else  if( en[counter] == '9'){
outcome = outcome + (9*power);
power = power*16;
counter--;
}

else  if( en[counter] == 'a'|| en[counter] == 'A'){
outcome = outcome + (10*power);
power = power*16;
counter--;
}

else  if( en[counter] == 'b'|| en[counter] == 'B'){
outcome = outcome + (11*power);
power = power*16;
counter--;
}

else  if( en[counter] == 'c'|| en[counter] == 'C'){
outcome = outcome + (12*power);
power = power*16;
counter--;
}

else  if( en[counter] == 'd'|| en[counter] == 'D'){
outcome = outcome + (13*power);
power = power*16;
counter--;
}

else  if( en[counter] == 'e'|| en[counter] == 'E'){
outcome = outcome + (14*power);
power = power*16;
counter--;
}

else  if( en[counter] == 'f'|| en[counter] == 'F'){
outcome = outcome + (15*power);
power = power*16;
counter--;
}
else{
fprintf(stderr,"ERROR! You entered a non-HEX number in a HEX string");
    exit(0);

}
}
return outcome;
}

//Given is Oct
else if(type == 'o' || type == 'O'){
int counter = strlen(en)-1;
int power =1;
int outcome =0;
while(counter != -1){
if(en[counter]=='1'){
outcome =outcome+ (1*power);
power = power *8;
counter--;
}
else if( en[counter] == '2'){
outcome = outcome + (2*power);
power = power*8;
counter--;
}

else if( en[counter] == '3'){
outcome = outcome + (3*power);
power = power*8;
counter--;
}

else if( en[counter] == '4'){
outcome = outcome + (4*power);
power = power*8;
counter--;
}

else if( en[counter] == '5'){
outcome = outcome + (5*power);
power = power*8;
counter--;
}

else if( en[counter] == '6'){
outcome = outcome + (6*power);
power = power*8;
counter--;
}

else if( en[counter] == '7'){
outcome = outcome + (7*power);
power = power*8;
counter--;
}
else{
fprintf(stderr,"ERROR! You entered a non-Oct number in a Oct string");
    exit(0);
}
}
return outcome;

}
return 0;
}

int add (int first, int second, int sign1, int sign2){
int temp;
if(sign1 == 1){
first = first *-1;}
if(sign2 ==1){
second = second * -1;}
//printf("first %d and second %d", first, second);
temp = first + second;
return temp;}

int subtract(int first, int second, int sign1, int sign2){
int temp;
if(sign1 == 1){
first =first * -1;}
if(sign2 ==1){
second =second *-1;}
//printf("first %d and second %d", first, second);
temp = first- second;
return temp;}

int multiply(int first, int second,int sign1, int sign2){
int temp;
if(sign1 == 1){
first =first * (-1);}
if(sign2 ==1){
second =second *-1;}
//printf("first %d and second %d", first, second);
temp = first * second;
return temp;}

int devide(int first, int second,int sign1, int sign2){
int temp;
if(sign1 == 1){
first = first * -1;}
if(sign2 ==1){
second =second *-1;}
//printf("first %d and second %d", first, second);
temp = first/second; 
return temp;}

int convertFinalForm(int n, char form){
//Convert from int to Binary
if( form == 'b' || form == 'B'){ 
 int remainder; 
    int binary = 0, i = 1;
     
    while(n != 0) {
        remainder = n%2;
        n = n/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}


//Convert from int to HexaDEcimal
else if( form == 'x' || form == 'X'){
long int decimalNumber,quotient;
    int i=1,j,temp;
    char hexadecimalNumber[100];

decimalNumber = n;

    quotient = decimalNumber;

    while(quotient!=0){
         temp = quotient % 16;

      //To convert integer into character
      if( temp < 10){
           temp =temp + 48;
      }
      else{
         temp = temp + 55;
      }

      hexadecimalNumber[i++]= temp;
      quotient = quotient / 16;
  }
printf("FIN: ");
    for(j = i -1 ;j> 0;j--){
      printf("%c",hexadecimalNumber[j]);
    }
printf("\n");
    exit(0);

}
//Convert from int to Octa
else if( form == 'o' || form == 'O'){
int rslt=0, digitPos=1;
     while (n) {
         rslt += (n%8)*digitPos;
        n /= 8;
         digitPos *= 10;     }
     return rslt;
}
//Convert from int to Decimal
else if( form == 'd' || form == 'D'){
return n;
}
 //Something is wrong , not final convertion detected
 else{
printf("ERROR! No final form detected");}
return 1;
}


int main (int argc , char** argv){
if( argc < 4 ){
fprintf(stderr,"ERROR! You did not enter the correct amount of arguments\n");
    exit(0);
}

Arguments *CurrentArg;
CurrentArg = parser(argv);
if(CurrentArg -> operation == '+' ){
CurrentArg ->final = add(CurrentArg->first, CurrentArg->second, CurrentArg->sign1, CurrentArg->sign2);
printf("FIN  : %d \n", convertFinalForm(CurrentArg->final, CurrentArg -> finalstate));
return 0 ;
}
if(CurrentArg -> operation == '-' ){
CurrentArg ->final = subtract(CurrentArg->first, CurrentArg->second, CurrentArg->sign1, CurrentArg->sign2);
printf("FIN  : %d \n", convertFinalForm(CurrentArg->final, CurrentArg -> finalstate));
return 0 ;
} 
if(CurrentArg -> operation == 'x' ){
CurrentArg ->final = multiply(CurrentArg->first, CurrentArg->second, CurrentArg->sign1, CurrentArg->sign2);
exit(0); 
}

if(CurrentArg -> operation == '/' ){
CurrentArg ->final = devide(CurrentArg->first, CurrentArg->second, CurrentArg->sign1, CurrentArg->sign2);
printf("FIN  : %d \n", convertFinalForm(CurrentArg->final, CurrentArg -> finalstate));
return 0 ;
}

return 0 ;


}


