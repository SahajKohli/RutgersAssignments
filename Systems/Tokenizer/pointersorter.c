//Sahaj Kohli
//Systems Programming
//Honest and simple Comments By Sahaj's Tired Brain
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//Decided to use An struct containing a array which is later dynamically allocatted
//Contains the array of words -> Contains
//the number of bytes being stored -> numWords
//the number of total indivdual words -> finalWords
typedef struct Word{

char** Contains;

int numWords;

int finalWords;
}Words;

//Only have two methods
//getWords will get indicuval words and tokenize them into seperate strings, excluding anything but charcthers
//sortWords will sort the array using Selection Sort
void getWords(int arg, char** argWords, Words* words);
void sortWords(Words* words);



///////*******Putting Words into an Array********/////////

void getWords(int arg, char** argWords, Words* words){


//Random int name
int ewm=1;

for(ewm =1 ; ewm< arg; ewm++){
int tempr = (strlen(argWords[ewm]) +1);
words->numWords = words->numWords + tempr;
}


int x = 1;
int y = 0;

words->Contains= malloc(words->numWords);


int written =0;
words->finalWords = 0;
for(x= 1; x<arg; x++){
	char* current= malloc(words-> numWords);
	int counter = 0;

//comparing the chars using isalpha
	for(y=0; y< strlen(argWords[x]); y++){
		
		if(isalpha(argWords[x][y])){
			written = 0;
			current[counter] = argWords[x][y];
			counter= counter +1;
			//printf(" current: %s counter: %d\n", current, counter);
				
		}
		else{
			if(counter != 0){
			//printf("Inside moving along\n");
			current[counter]='\0';
                        //char* temp = malloc(sizeof(current));
                        //strcpy(current, current);
                        words->Contains[words->finalWords] = current;
                        //printf(" In Stuct: %s\n", words->Contains[words->finalWords]);
			counter= 0;
			current = malloc(words->numWords);written = 1;
			words->finalWords = words->finalWords + 1;	
			}
			else{written = 1;
				}}
	
		}
		
		if(written == 0){
		
		 current[counter]='\0';
                        //char* temp = malloc(sizeof(current));
                        //strcpy(current, current);
                 words->Contains[words->finalWords] = current;
                // printf(" In Stuct: %s\n", words->Contains[words->finalWords]);
		words->finalWords = words->finalWords + 1;
	}

}

sortWords(words);
}


//////*******SORTING*********///////
//
//Using Selection Sort to actively compare and sort

void sortWords(Words* words){

int x = 0;
int y = 0;
int smallest = 0;
for(x = 0; x<words->finalWords ; x++){
	char* curr = malloc(strlen(words->Contains[x]));
        strcpy(curr, words->Contains[x]);
	smallest= x;
	y=x;
		for(; y< words->finalWords; y++){
	//printf("Comparing to  %s \n", words->Contains[y]);
	
		int ret = strcmp(curr, words->Contains[y]);
			//if the current token is the smaller one
   			if(ret < 0){
      			 continue;
				}	
			//if something smaller was found
   			else if(ret > 0){
			curr = malloc(strlen(words->Contains[y]));
        		strcpy(curr, words->Contains[y]);
			smallest = y;}
   			//if something is equal nothing is done because it will then be picked up later and compared
			else{}
		}
//finialize the sort by removing whats at the front sorted side and changing it with new smallest
	char* temp = malloc(strlen(words->Contains[x]));
	strcpy(temp, words->Contains[x]);
	words->Contains[x]=curr;
	words->Contains[smallest]=temp;
}
}


//*****************************//
int main(int argc, char** argv){

//Having a Little fun with the string modifers :)
printf("\033[5;33mAssignment 0 : Systems Programming\033[0m \n");
printf("\033[1;33mProgram by Sahaj Kohli\033[0m \n");
//No More fun.....only useful and good code from here

//checking for illegal arguments
	if(argc == 0){
	printf("Please input a value/n");
	return 1;
	}
clock_t begin = clock();
double s = (double)begin *100000;
printf("%f\n", s);
Words *currWords = malloc(sizeof(Words)); 
//printf("Mem located\n");

//Passing the input to get tokenized and then sorted. getWords will call sort method
getWords(argc, argv, currWords);


	int reg= 0;
	//regular for loop to go through everything in the array and dump it
	for ( reg = 0 ; reg < currWords->finalWords; reg++){
        	printf("FINAL : %s  \n", currWords->Contains[reg]);
	}

clock_t end = clock();
double e = (double)end*100000;
printf("%f\n", e);
double time_spent = (((double)(e-s))*100000000)/CLOCKS_PER_SEC; 
printf("Time Of Execution: %f \n", time_spent);
return 0;
}

