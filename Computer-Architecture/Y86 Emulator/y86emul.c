#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y86emul.h"

char * reg;
unsigned int registerBytes;
unsigned long jmpAddr;
char* tester;
unsigned int progCounter; int strt;int end;unsigned long sizeOfStack;unsigned char * y86;int ZF = 0, SF = 0, OF = 0;unsigned long regs[8] = {0, 0, 0, 0, 0, 0, 0, 0};

//First go through and heck the directives given. Called upon from another place. Will check to make sure
//that the actual inputs are good before executing
//Checks for the Size Directive
void sizeDirective(char * tok){
	tok = strtok(NULL, "\t\"");
	//converting hexto UNsigned
	sizeOfStack = hextodecUnsigned(tok, y86);
	//Setting up for the size of the Array (Stack)
	y86 = (char *) calloc(1, sizeOfStack + 1);
}
//Cheaking for the String Directive
void stringDirective(char * tok){
	tok = strtok(NULL, "\t\"");
	//converting hexto UNsigned
	unsigned long place = hextodecUnsigned(tok, y86);
	tok = strtok(NULL, "\t\"");
	int i;
	for(i = 0; i < strlen(tok); i++)
	{y86[place + i] = tok[i];
	}
}
//Checking for the Long Directive
void longDirective(char * tok){
	tok = strtok(NULL, "\t\"");
	//converting hexto UNsigned
	unsigned long place = hextodecUnsigned(tok, y86);
	tok = strtok(NULL, "\t\"");
	*((int *) &y86[place]) = atoi(tok);}

//cheaking for the BSS directive
void bssDirective(char * tok){
	tok = strtok(NULL, "\t\"");
	//converting hexto UNsigned
	unsigned long place = hextodecUnsigned(tok, y86);
	tok = strtok(NULL, "\t\"");
	int size = atoi(tok);int i;
	for(i = 0; i <= size; i++){
		y86[place + i] = (long) NULL;
	}
}
//checking for the byte directive
void byteDirective(char * tok){
	tok = strtok(NULL, "\t\"");
	//converting hexto UNsigned
	unsigned long place = hextodecUnsigned(tok, y86);
	tok = strtok(NULL, "\t\"");
	char byte[3];
	byte[0] = tok[0];
	byte[1] = tok[1];
	byte[2] = '\0';
	unsigned long byteValue = hextodecUnsigned(byte, y86);
	y86[place] = (unsigned char)byteValue;
}
//checking for the text directive
void textDriective(char * tok){
	tok = strtok(NULL, "\t\"");
	//converting hexto UNsigned
	unsigned long place = hextodecUnsigned(tok, y86);
	progCounter = place;
	strt = progCounter;
	tok = strtok(NULL, "\t\"");
	int i;
	char onebyte[3];
	for(i = 0; i < strlen(tok); i+=2){
		onebyte[0] = tok[i];
		onebyte[1] = tok[i+1];
		onebyte[2] = '\0';
		y86[place] = hextobyte(onebyte, y86);
		place++;
	}
	end = place;
}

//Actual Executaiton of the instrcutions happens in this switch statemtn
void Execution(){
	while(progCounter < end){
		unsigned int instruction = (unsigned int) y86[progCounter];
		if(progCounter < strt){
			exit(1);}
		switch (instruction){
			//following the instruciton and decoding them
			case 0x00: progCounter++; break;
			case 0x10:
			//	printf("HALTED\n");
			//print statement for testing puposes
				printf("\nInstruction set has been stopped @ = 0x%x. STATUS: HLT\n", progCounter);
				exit(1);; progCounter++; break;

			case 0x20:
			//	printf("rmmovl\n");
			//print statement for testing puposes
			tester ="yeah";
	  		registerBytes = y86[progCounter + 1];
	  		 reg = getByteChars(registerBytes, y86);
				if(reg[0] >= 'a' || reg[1] >= 'a'){
					printf("Incorrect Register Identifier.\n");
					exit(1);}
				else{
					regs[reg[1] - '0'] = regs[reg[0] - '0'];
				}; progCounter += 2; break;

			case 0x30:
			//	printf("irmovl\n");
			//print statement for testing puposes
				registerBytes = y86[progCounter + 1];
				 reg = getByteChars(registerBytes, y86);
				if(reg[0] != 'f' || reg[1] >= 'a'){
				printf("Incorrect Register Identifier.\n");
				exit(1);}
				else{
				long immediate = getImmediateValue(progCounter + 2, y86);
				regs[reg[1] - '0'] = immediate;};
				 progCounter += 6; break;

			case 0x40:
				//printf("rmmovl\n");
				//print statement for testing puposes//here
				registerBytes = y86[progCounter + 1];
				reg = getByteChars(registerBytes, y86);
				if(reg[0] >= 'a' || reg[1] >= 'a'){
					printf("Incorrect Register Identifier.\n");
					exit(1);}
				else{
				long displacement = getImmediateValue(progCounter + 2, y86);
				*((int *) &y86[displacement + regs[reg[1] -'0']]) = regs[reg[0] - '0'];}
				progCounter += 6; break;

			case 0x50:
			//	printf("mrmovl\n");
			//print statement for testing puposes
				registerBytes = y86[progCounter + 1];
				reg = getByteChars(registerBytes, y86);
				if(reg[0] >= 'a' || reg[1] >= 'a'){
				printf("Incorrect Register Identifier.\n");
				exit(1);}
				else{
				long displacement = getImmediateValue(progCounter + 2, y86);
				regs[reg[0] - '0'] = *((int *) &y86[displacement + regs[reg[1] - '0']]);};
				progCounter += 6; break;

			case 0x60:
			//	printf("add1\n");
			//print statement for testing puposes
				registerBytes = y86[progCounter + 1];
				reg = getByteChars(registerBytes, y86);
				OF = 0;
				SF = 0;
				ZF = 0;
				if(reg[0] >= 'a' || reg[1] >= 'a'){
				printf("Incorrect Register Identifier.\n");
				exit(1);}
				else{
				long long sum = regs[reg[1] - '0'] + regs[reg[0] - '0'];
				if((regs[reg[0]] > 0 && regs[reg[1]] > 0 && sum < 0) ||
				   (regs[reg[0]] < 0 && regs[reg[1]] < 0 && sum > 0) ||
				   (sum > (power(2, 31, y86) - 1)) || (sum < (-1 * power(2,31, y86)))){
					OF = 1;
					printf("Overflow Detected  @: %x\n", progCounter);}
				if(sum == 0){
					ZF = 1;}
				else if(sum < 0){
					SF = 1;}
					regs[reg[1] - '0'] = (long) sum;}
					progCounter += 2; break;

			case 0x61:
			//	printf("subl\n");
			//print statement for testing puposes
				registerBytes = y86[progCounter + 1];
				reg = getByteChars(registerBytes, y86);
				ZF = 0;
				SF = 0;
				OF = 0;
				if(reg[0] >= 'a' || reg[1] >= 'a'){
				printf("Incorrect Register Identifier.\n");
				exit(1);}
				else{
				long long difference = regs[reg[1] - '0'] - regs[reg[0] - '0'];
				if((regs[reg[0]] < 0 && regs[reg[1]] > 0 && difference < 0) ||
				   (regs[reg[0]] > 0 && regs[reg[1]] < 0 && difference > 0) ||
				   (difference > power(2, 31, y86) - 1) || (difference < (-1 * power(2,31, 86)))){
					OF = 1;
					printf("Overflow Detected @ : %x\n", progCounter);}
				if(difference == 0){
					ZF = 1;}
				else if(difference < 0){
					SF = 1;}
				regs[reg[1] - '0'] = (long) difference;}
			 	progCounter += 2; break;

			case 0x62:
			//	printf("and1\n");
			//print statement for testing puposes
				registerBytes = y86[progCounter + 1];
				reg = getByteChars(registerBytes, y86);
				ZF = 0;
				SF = 0;
				if(reg[0] >= 'a' || reg[1] >= 'a'){
					printf("Incorrect Register\n");
					exit(1);}
				else{
					long and = regs[reg[1] - '0'] & regs[reg[0] -'0'];
				if(and == 0){
				ZF = 1;	}
			else if (and < 0){
				SF = 1;}
			regs[reg[1] - '0'] = and;}
			 progCounter += 2; break;

			case 0x63:
			 //	printf("xorl\n");
			 //print statement for testing puposes
				registerBytes = y86[progCounter + 1];
				reg = getByteChars(registerBytes, y86);
				ZF = 0;
				SF = 0;
				if(reg[0] >= 'a' || reg[1] >= 'a'){
				printf("Incorrect Register Identifier");
				exit(1);}
				else{
				long xor = regs[reg[1] - '0'] ^ regs[reg[0] -'0'];
				if(xor == 0){
					ZF = 1;}
				else if (xor < 0){
					SF = 1;}
				regs[reg[1] - '0'] = xor;}
				progCounter += 2; break;

			case 0x64:
				//printf("mull\n");
				//print statement for testing puposes
				registerBytes = y86[progCounter + 1];
				reg = getByteChars(registerBytes, y86);
				ZF = 0;
				SF = 0;
				OF = 0;
				if(reg[0] >= 'a' || reg[1] >= 'a')	{
					printf("Incorrect Register Identifier");
					exit(1);}
				else	{
					long long product = regs[reg[0] - '0'] * regs[reg[1] - '0'];
					if((regs[reg[0]] > 0 && regs[reg[1]] > 0 && product < 0) ||
					   (regs[reg[0]] < 0 && regs[reg[1]] < 0 && product > 0) ||
					   (regs[reg[0]] < 0 && regs[reg[1]] > 0 && product > 0) ||
					   (regs[reg[0]] > 0 && regs[reg[1]] < 0 && product > 0) ||
					   product > power(2, 32, y86) - 1 || product < (-1 * power(2, 31, y86))){
						OF = 1;
						printf("Overflow Detected @: %x\n", progCounter);}
					if(product == 0)	{
						ZF = 1;}
					else if(product < 0){
						SF = 1;}
					regs[reg[1] - '0'] = (long) product;}
					 progCounter += 2; break;

					 case 0x65:
				 	//printf("cmpl\n");
				 	//print statement for testing puposes
				 		registerBytes = y86[progCounter + 1];
				 		reg = getByteChars(registerBytes, y86);
				 		ZF = 0;
				 		SF = 0;
				 		OF = 0;
				 		if(reg[0] >= 'a' || reg[1] >= 'a'){
				 		printf("Incorrect Register Identifier.\n");
				 		exit(1);}
				 		else{
				 		long difference = regs[reg[1] - '0'] - regs[reg[0] - '0'];
				 		if((regs[reg[0]] < 0 && regs[reg[1]] > 0 && difference < 0) ||
				 			 (regs[reg[0]] > 0 && regs[reg[1]] < 0 && difference > 0) ||
				 			 (difference > power(2, 31, y86) - 1) || (difference < (-1 * power(2,31, 86)))){
				 			OF = 1;
				 			printf("Overflow Detected @ : %x\n", progCounter);}
				 		if(difference == 0){
				 			ZF = 1;}
				 		else if(difference < 0){
				 			SF = 1;}
				 	//regs[reg[1] - '0'] = (long) difference;
				}
					//	printf(" ZF: %d\n",ZF );
					//	printf(" SF: %d\n",SF );
					//	printf(" OF: %d\n",OF );

				 		progCounter += 2; break;

			case 0x70:
				jmpAddr = getplaceValue(progCounter + 1, y86);
			//	printf("Jump place: %x\n", jmpAddr);
			//print statement for testing puposes
				if(jmpAddr < strt || jmpAddr > end){
					printf("Incorrect instructions");
					exit(1);}
				else{
					progCounter = jmpAddr;}
				break;

			case 0x71:
				jmpAddr = getplaceValue(progCounter + 1, y86);
				//printf("Jump place: %x\n", jmpAddr);
				//print statement for testing puposes
				if(jmpAddr < strt || jmpAddr > end){
					printf("Incorrect instructiond Detected");
					exit(1);}
				else{
					if((SF ^ OF) | ZF)
						progCounter = jmpAddr;
					else
						progCounter += 5;}
				break;

			case 0x72:
				jmpAddr = getplaceValue(progCounter + 1,y86);
			//	printf("Jump place: %x\n", jmpAddr);
			//print statement for testing puposes
				if(jmpAddr < strt || jmpAddr > end){
					printf("Incorrect Insturctions Detected");
					exit(1);}
				else{
					if(SF ^ OF)
						progCounter = jmpAddr;
					else
						progCounter += 5;}
				break;

			case 0x73:
				jmpAddr = getplaceValue(progCounter + 1, y86);
			//	printf("Jump place: %x\n", jmpAddr);
			//print statement for testing puposes
				if(jmpAddr < strt || jmpAddr > end){
					printf("Incorrect Insturctions Detected");
					exit(1);}
				else{
					if(ZF == 1)
						progCounter = jmpAddr;
					else
						progCounter += 5;}
				 break;

			case 0x74:
				jmpAddr = getplaceValue(progCounter + 1, y86);
			//	printf("Jump place: %x\n", jmpAddr);
			//print statement for testing puposes
				if(jmpAddr < strt || jmpAddr > end){
					printf("Incorrect Insturctions Detected");
					exit(1);}
				else{
					if(ZF == 0)
						progCounter = jmpAddr;
					else
						progCounter += 5;}
				break;

			case 0x75:
				jmpAddr = getplaceValue(progCounter + 1, y86);
			//	printf("Jump place: %x\n", jmpAddr);
			//print statement for testing puposes
				if(jmpAddr < strt || jmpAddr > end){
				printf("Incorrect Insturctions Detected");
				exit(1);}
				else{
				if((SF^OF) == 0)
					progCounter = jmpAddr;
				else
					progCounter += 5;}
					break;

			case 0x76:
				jmpAddr = getplaceValue(progCounter + 1, y86);
			//	printf("Jump place: %x\n", jmpAddr);
			//print statement for testing puposes
				if(jmpAddr < strt || jmpAddr > end){
				printf("Incorrect Insturctions Detected");
				exit(1);}
				else{
				if(~(SF ^ OF) & ~ZF)
					progCounter = jmpAddr;
				else
					progCounter += 5;}
			 	break;

			case 0x80:
			//	printf("call\n");
			//print statement for testing puposes
		tester = "yeaher";
				unsigned long place = getplaceValue(progCounter + 1, y86);
				progCounter += 5;
				if(place < strt || place > end){
					printf("Incorrect Insturctions Detected");
					exit(1);}
				else{
					regs[4] -= 4;
					*((int *) &y86[regs[4]]) = progCounter;
					progCounter = place;}
				break;

			case 0x90:
				//printf("ret\n");
				//print statement for testing puposes
				progCounter = *((int*)&y86[regs[4]]);
				regs[4] += 4; break;

			case 0xa0:
			//	printf("HALTED\n");
			//print statement for testing puposes
				registerBytes = y86[progCounter + 1];
				reg = getByteChars(registerBytes, y86);
				if(reg[0] >= 'a' || reg[1] != 'f'){
					printf("Wrong Register Detected");
					exit(1);}
				else{
					regs[4] -= 4;
					*((int*) &y86[regs[4]]) = regs[reg[0] - '0'];}
					progCounter += 2; break;

			case 0xb0:
				//printf("popl\n");
				//print statement for testing puposes
				registerBytes = y86[progCounter + 1];
				reg = getByteChars(registerBytes, y86);
				if(reg[0] >= 'a' || reg[1] != 'f'){
					printf("Wrong Register Detected");
					exit(1);}
				else{
					regs[reg[0] - '0'] = *((int *) &y86[regs[4]]);
					regs[4] += 4;}
					progCounter += 2; break;

			case 0xc0:
			//	printf("readb\n");
			//print statement for testing puposes
				registerBytes = y86[progCounter + 1];
				reg = getByteChars(registerBytes, y86);
				ZF = 0;
				if(reg[0] >= 'a' || reg[1] != 'f'){
					printf("Wrong Register Detected");
					exit(1);}
				else{
					long immediate = getImmediateValue(progCounter + 2, y86);
					char byte[3];
					byte[2] = '\0';
					if(scanf("%hhx", byte) != EOF)
					{
						long place = regs[reg[0] - '0'] + immediate;
						if(place < end){
							printf("ERROR");
							exit(1);}
						else{
							if(byte[0] > 'f' || byte[1] > 'f'){
								printf("ERROR:Please enter correct format \n");}
							else{
								y86[place] = hextodecUnsigned(byte, y86);
								if(y86[place] == 0)	{
									ZF = 1;
								}
							}
						}
					}
					else{
						ZF = 1;
					}
				}
				 progCounter += 6; break;

			case 0xc1:
			//	printf("readl\n");
			//print statement for testing puposes
				registerBytes = y86[progCounter + 1];
				reg = getByteChars(registerBytes, y86);
				ZF = 0;
				if(reg[0] >= 'a' || reg[1] != 'f'){
					printf("Wrong Register Detected");
					exit(1);	}
				else{
					long immediate = getImmediateValue(progCounter + 2, y86);
					unsigned long int word[32];
					word[31] = '\0';
					if(scanf("%ld", word) != EOF){
						*((unsigned long int *) (&y86[regs[reg[0] - '0'] + immediate])) = *word;
						if(*((unsigned long int *) (&y86[regs[reg[0] - '0'] + immediate])) == 0 ){
							ZF = 1;
						}
					}
					else{
						ZF = 1;
					}
				}
				 progCounter += 6; break;

			case 0xd0:
			//	printf("wrtieb\n");
			//print statement for testing puposes
				registerBytes = y86[progCounter + 1];
				reg = getByteChars(registerBytes, y86);
				if(reg[0] >= 'a' || reg[1] != 'f'){
				printf("Wrong Register Detected");
				exit(1);}
			else{
				long immediate = getImmediateValue(progCounter + 2, y86);
				unsigned char byte = (unsigned char) y86[regs[reg[0] - '0'] + immediate];
				printf("%c", byte);}
				progCounter += 6; break;

			case 0xd1:
			//	printf("writel\n");
			//print statement for testing puposes
				registerBytes = y86[progCounter + 1];
				reg = getByteChars(registerBytes, y86);
				if(reg[0] >= 'a' || reg[1] != 'f'){
				printf("Wrong Register Detected");
				exit(1);}
			else{
				long immediate = getImmediateValue(progCounter + 2, y86);
				unsigned long int word = *((int *) &y86[regs[reg[0] - '0'] + immediate]);
				printf("%ld", word);}
				progCounter += 6; break;

			case 0xe0:
				//printf("movsbl\n");
				//print statement for testing puposes
				registerBytes = y86[progCounter + 1];
				reg = getByteChars(registerBytes, y86);
				if(reg[0] >= 'a' || reg[1] >= 'a'){
				printf("Incorrect Register Identifier.\n");
				exit(1);}
				else{
				long displacement = getImmediateValue(progCounter + 2, y86);
				regs[reg[0] - '0'] =  y86[displacement + regs[reg[1] - '0']];
			}
				progCounter += 6; break;


			default: fprintf(stderr, "Instruction set stopped Execution of progCounter at = 0x%x. STATUS: INS\n" , progCounter); exit(1); break;
		}
	}
}

void main(int argc, char * argv[]){
	printf("Welcome to the y86emul, enter '-h' for help on return\n");
	if(strcmp(argv[1], "-h") == 0){
		printf("y86emul will take a textfile and execute ASCII y8 instructions\n");
		exit(1);}
	FILE * y86file = fopen(argv[1], "r");
	if(y86file == NULL){
		fprintf(stderr, "ERROR:Please check file name and location, the file was not found\n");
		exit(1);} char line[90000];
	fgets(line, sizeof(line)/sizeof(char), y86file);
	char * tokenized = strtok(line, "\t\"");
	if(strcmp(tokenized, ".size") != 0){
		fprintf(stderr, "ERROR: No direction found!!.\n");
		exit(1);}
	else{
		sizeDirective(tokenized);}
	int textFlag = 0;
	memset(tokenized, 0, sizeof(tokenized)/sizeof(char));
	while(fgets(line, sizeof(line)/sizeof(char), y86file)){
		tokenized = strtok(line, "\t\"");
		if(strcmp(tokenized, ".string") == 0){
			stringDirective(tokenized);}
		else if(strcmp(tokenized, ".long") == 0){
			longDirective(tokenized);}
		else if(strcmp(tokenized, ".bss") == 0){
			bssDirective(tokenized);}
		else if(strcmp(tokenized, ".byte") == 0){
			byteDirective(tokenized);}
		else if(strcmp(tokenized, ".text") == 0){
			if(textFlag == 0){
				textFlag == 1;
				textDriective(tokenized);}
			else{
				fprintf(stderr, "ERROR: Problem in file format, the diretives are incorrect\n");
				exit(1);}	}
		memset(tokenized, 0, sizeof(tokenized)/sizeof(char));}
		Execution();
	free(y86);
}
