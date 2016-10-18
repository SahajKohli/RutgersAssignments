/*Sahajdeep Kohli
 * CS211, Computer Architecture
 * Brian, Russel
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

//Creation of global variables
//State will hold the state of the token
//mal will hold the malformed char in tokens, which will be later printed in HEX
//temp is a pointer to char array that will be passed around contained the current token
char* STATE;
char mal;
char* temp;

//Prototype Declaration for future Use in program
char* stateZero(char*p);
char* stateInt(char*p);
char* stateFloat(char*p);
char* stateE(char*p);
char* stateMal(char*p);
char* stateHex(char*p);
char* stateOctal(char*p);


//The struct contains two char array pointers
//Whole:  will the counter that holds the entire String and will be decremented as the programs, the tokencurrently being worked on will be put into the temp char pointer
//Curr: will be the current token, only used for printing when the state of the token of the token has  been found
struct TokenizerT_ {
char*whole;
char*curr;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
TokenizerT *tk = malloc(sizeof(TokenizerT*));

//mallocing additional memory for whole and curr, otherwise segmentation fault occurs
tk->whole = malloc(strlen(ts)+1);
tk->curr = malloc(strlen(ts)+1);

strcpy(tk->whole, ts);
strcpy(tk->curr, tk->whole);
//malloc memory for the globals
// will free this memory when destory token is called
STATE=malloc(30);


  return tk;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
//freeing up all the mallocs
//free((char *) STATE);
//free((char *) tk->curr);
//free((char *) tk->whole);
free(tk);
}


//***************************STATE FUNCTIONS*******************************


//BLANK STATE
//the blankState function is where everything goes, first stage of the FSM
//checks if equal to 0 for octa, checks for digit, and space incase for unwanted 
char* blankState(char* p){
	if(p[0] == '0'){
	return stateZero(p=p+1);
	}

	else if(isdigit(p[0])){
	return stateInt(p=p+1);
	}
	
	else if(isspace(p[0])){
	return stateMal(p=p+1);
	}

	else{
	mal=p[0];
	return stateMal(p=p+1);
	}	
}

//ZERO STATE
//stateZero is where anything starting with Zero would go, it will check whether it is a Hexadecimal, exponential, octal or a ZERO
//returns MAL is anything else
char* stateZero(char* p){
	if(p[0] == 'x' || p[0] == 'X'){
	return stateHex(p=p+1);
	}
	
	else if(p[0] == '.'){
	return stateFloat(p=p+1);
	}
	
	else if(p[0]=='1'|| p[0]=='2'|| p[0]=='3'|| p[0]=='4'|| p[0]=='5'|| p[0]=='6'|| p[0]=='7'){
	return stateOctal(p=p+1);
	}

	else if(p[0]=='\0' || p[0]==0){
	return "Zero";
	}
	
	else if(p[0]=='e' || p[0]=='E'){
	return stateE(p=p+1);
	}
	
	else{
	mal = p[0];
	return stateMal(p=p+1);
	}	 

}

//INTEGER STATE
//stateInt will check if the char is float or expo or int
//if the char is int then it will recursively call itself 
//anything that is not one of these will be malformed
char* stateInt(char* p){
	if(isdigit(p[0])){
	return stateInt(p=p+1);
	}
	
	else if( p[0]=='.'){
	return stateFloat(p=p+1);
	}
	
	else if(p[0]=='e'){
	return stateE(p=p+1);
	}
	
	else if(p[0]=='\0' || p[0]== 0){
	return "Integer";
	}
	
	else{
	mal = p[0];
	return stateMal(p=p+1);
	}
	
}

//FLOAT STATE
//stateFloat will check if the char is a exponent or a digit
//anything else will be discarded
//the function will call itself if it is digit, continue until end of token or another condition
char* stateFloat(char* p){
	if(isdigit(p[0])){
	return stateFloat(p=p+1);
	}

	else if(p[0]=='e'|| p[0]=='E'){
	return stateE(p=p+1);
	}
	
	else if(p[0]=='\0' || p[0]=='0'){
	return "Float";
	}
	
	else{
	mal=p[0];
	return stateMal(p=p+1);
	}	
}

//EXPONENTIAL STATE
//stateE checks if the token is a float
//it wil check for '+' or '-' signs and digits
//in both cases the function will call itself because there is nothing else you can input
char* stateE(char*p){
	if(p[0]=='+' || p[0]=='-'){
	return stateE(p=p+1);
	}
	
	else if (isdigit(p[0])){
	return stateE(p=p+1);
	}
		
	else if(p[0]=='\0' || p[0]=='0'){
	return "Exponent";
	}
	
	else{
	mal= p[0];
	return stateMal(p=p+1);
	}
}

//HEX STATE
//stateHex will check for 1-9 and a-f and A-F 
//also will check if it not one of those things
//it will call itself it fits one of those above, otherwise it is mal or the string is ended
char* stateHex(char*p){
	if(p[0]== '1'||p[0] == '2'||p[0] == '3'||p[0] == '4'||p[0] == '5'||p[0] == '6'||p[0] == '7'||p[0] == '8'||p[0] == '9'||p[0] == 'a'||p[0] == 'b'||p[0] == 'c'||p[0] == 'd'||p[0] == 'e'||p[0] == 'f'||p[0] == 'A'||p[0] == 'B'||p[0] == 'C'||p[0] == 'D'||p[0] == 'E'||p[0] == 'F'){
	return stateHex(p=p+1);
	}
	
	else if(p[0]== '\0' || p[0]==0){
	return "Hex";
	}

	else{
	mal = p[0];
	return stateMal(p=p+1);
	}

}

//OCTAL STATE
//The octal state will check if the numbers are from 1-8 
//if anything else the token is malformed
char* stateOctal(char*p){
	if(p[0]=='1'|| p[0]=='2'|| p[0]=='3'|| p[0]=='4'|| p[0]=='5'|| p[0]=='6'|| p[0]=='7'){
	return stateOctal(p=p+1);
	}
	
	else if (p[0]=='\0' || p[0]==0){
	return "Octal";
	}
	
	else{
	mal = p[0];
	return stateMal(p=p+1);
	}

} 

//MALFORMED STATE
//stateMal is where all of the Malformed tokens will go
//stateMAl is created so that the recursive cycle can be completed before sending the tokens back
char* stateMal(char*p){
	if(p[0]=='\0' || p[0]==0){
	return "Malformed";
	}
	
	else{
	return stateMal(p=p+1);
	}
	
}	


//********************************END OF STATE FUNCTIONS*************************



/*
*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
//**** Copier and Temp will be freed in this function******
temp = malloc(strlen(tk->whole)+1);
char*copier;
//copier is used to increment the tokens
copier= malloc(strlen(tk->whole)+1);
strcpy(copier,tk->whole );
int count;
	//for loop will go through the string until it finds a escape char or end of string
	for(count = 0 ; count< strlen(copier); count++, tk->whole++){
		if(copier[count+1] == '\0'|| tk->whole[1] == '\0'){

			tk->whole++;
			strncpy(temp, copier + 0, (count+1) - 0);
			strcpy(tk->curr, temp);
			STATE = blankState(temp);
                 	break;		
 		}

 		else if(isspace(copier[count])){

			tk->whole++;
			strncpy(temp, copier + 0, count - 0);
                        strcpy(tk->curr, temp);
			 STATE = blankState(temp);
                        break;	
		}	
		else if(isdigit(copier[count])){
                	continue;
        	}	
	

         	else if(copier[count] == '.'){
                        continue;
        	}

                else if(copier[count] == 'a'|| copier[count] ==  'b' || copier[count] ==  'c' || copier[count] ==  'd' || copier[count] ==  'e'|| copier[count] ==  'f' || copier[count] ==  'x' ){
                        continue;

        	}
	
		else{
                        continue;
       		}
	}
  
//will print out MALFORMED states, along with chars in HEX and the Token given  
//if any token has a malformed char the entire token will be calle malformed
//	if(strcmp( STATE, "Malformed") == 0){
if(STATE =="Malformed"){
		printf("\033[1;31mSTATE:%s  \033[0m \n", STATE);
		printf("\033[1;31mToken given:%s \033[0m \n" , tk->curr);
        	printf("\033[1;31mThe Malformed Char is: %c, given the HEX value: %04x \033[0m \n", mal,		 mal);
        	printf("\033[1;31m-----------------------\033[0m \n"); 
		//freeing up TEMP and COPIER
		free(temp);
		free(copier);
        	return temp;
		//returning temp, nothing in it, doesn't really do anything
        }

	else{
		printf("\033[1;34mThe String Provided was: %s \033[0m \n" , tk->curr);
		printf("\033[1;34mSTATE: %s  \033[0m \n", STATE);
        	printf("\033[1;34m-------------------\033[0m \n");
		//freeing up TEMP and COPIER
		free(temp);
		free(copier);
		return temp;
        	//returning temp again, doesn't really do anything
	 }	

}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
printf("\033[5;33mWelcome to the Tokenizer\033[0m \n");
TokenizerT *tk;
char* ret;
ret= malloc(30);
tk= TKCreate(argv[1]);
printf("\033[1;33mProgram by Sahaj Kohli\033[0m \n");
	//whille loop will call upon getnext until whole is empty
	while(tk->whole[0] != '\0'){
	ret = TKGetNextToken(tk);	
	}		
TKDestroy(tk); 	
return 0;}
