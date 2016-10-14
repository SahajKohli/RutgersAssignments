#include <mymalloc.h>


//The following functions are used to look at 4 distinct segregated linked lists and see if there's anything in them
//if there is something in those linked lists then we allocate the size required while also creating a new division if the size if not perfect fit
char * takeFromLL1 ( int sizeWanted){
	//check if linked list is empty
	short* temp1 = myblock[0];
	if(*temp1 == 0){
		//recursively try to find the list with anything in it
		return takeFromLL2(sizeWanted);
	}
	//else there is actually something in this linked list
	else{
		short ind = *temp1;
		short* nextNode = &myblock[ind + 9];
		short* sizecurrent = &myblock[ind];
		short* prev;

		while(true){
			//found the one that would be able to fit the required size
			if(*sizecurrent >= sizeWanted){
				//have to either split the current linked list or give it back
				if(*sizecurrent> sizeWanted){
					char allo = 'a';
					myblock[ind+currArch] = allo;
					short sizer = *sizecurrent - sizeWanted;
					*sizecurrent = sizeWanted;
					

					//creating new block of whatever is left over
					char* charsizer = &myblock[ind + 17 + sizeWanted];
					short currsizer = (short*)charsize;
					*currsizer = currblocksize;
		
					//1 byte char stating whether the thing is allocated or not
					char allocatedr = 'u';
					&myblock[ind + 17 + sizeWanted + currArch] = allocatedr;
		
					//creating the node in the block for the linkeed list
					char* linkedlistr = &myblock[ind + 17 + sizeWanted+ currArch + 1];
					short currllr = (short*)linkedlist; 
					//if we didnt remove the front node
					if( *temp1 != ind){
						short * prevNode = &myblock[previndex+1];
						*prevNode = ind + 17 + sizeWanted;
						*currllr = *myblock[ind + 8 + 1];

					}
					//if the node that was removed was the first node
					else{
						currllr = *myblock[ind + 8 + 1];
						short* linkedlist1 = &myblock[0];
			 			*linkedlist1 = nextblockIndex;

					}
					return &myblock[ind+ 1+ 8];



				}
				//if the size matches perfectly
				else{
					char allo = 'a';
					myblock[ind + 8 ] = allo;

					if( *temp1 != ind){
						short * prevNode = &myblock[previndex+1];
						*prevNode = ind + 17 + sizeWanted;
						*currllr = *myblock[ind + 8 + 1];

					}
					//if the node that was removed was the first node
					else{
						currllr = *myblock[ind + 8 + 1];
						short* linkedlist1 = &myblock[0];
			 			*linkedlist1 = nextblockIndex;

					}
					return &myblock[ind + 1+ 8];

				}
				break;
			}
			else{
				if(*nextNode == 0 ){
					//move to the next linked list because this one doesn't have right size
					return takeFromLL2(sizeWanted);
				}
				else{
					//size current is changed to index saved in the linked list short
					//ind is the current index which is now saved to nextnode
					//sizecurrent is 
					previndex = ind;
					sizecurrent = &myblock[*nextNode];
					ind = *nextNode;
					sizecurrent = &myblock[ind]
					nextnode = &myblock[ind + 9];

				}
			}
		}

	}

}




char * takeFromLL2 ( int sizeWanted){
	//check if linked list is empty
	short* temp2 = myblock[adjCurrArch];
	if(*temp2 == 0){
		//recursively try to find the list with anything in it
		return takeFromLL3(sizeWanted);
	}
	//else there is actually something in this linked list
	else{
		short ind = *temp1;
		short* nextNode = &myblock[ind + 9];
		short* sizecurrent = &myblock[ind];
		short* prev;

		while(true){
			//found the one that would be able to fit the required size
			if(*sizecurrent >= sizeWanted){
				//have to either split the current linked list or give it back
				if(*sizecurrent> sizeWanted){
					char allo = 'a';
					myblock[ind+currArch] = allo;
					short sizer = *sizecurrent - sizeWanted;
					*sizecurrent = sizeWanted;
					

					//creating new block of whatever is left over
					char* charsizer = &myblock[ind + 17 + sizeWanted];
					short currsizer = (short*)charsize;
					*currsizer = currblocksize;
		
					//1 byte char stating whether the thing is allocated or not
					char allocatedr = 'u';
					&myblock[ind + 17 + sizeWanted + currArch] = allocatedr;
		
					//creating the node in the block for the linkeed list
					char* linkedlistr = &myblock[ind + 17 + sizeWanted+ currArch + 1];
					short currllr = (short*)linkedlist; 
					//if we didnt remove the front node
					if( *temp1 != ind){
						short * prevNode = &myblock[previndex+1];
						*prevNode = ind + 17 + sizeWanted;
						*currllr = *myblock[ind + 8 + 1];

					}
					//if the node that was removed was the first node
					else{
						currllr = *myblock[ind + 8 + 1];
						short* linkedlist1 = &myblock[adjCurrArch];
			 			*linkedlist1 = nextblockIndex;

					}
					return &myblock[ind+ 1+ 8];



				}
				//if the size matches perfectly
				else{
					char allo = 'a';
					myblock[ind + 8 ] = allo;

					if( *temp1 != ind){
						short * prevNode = &myblock[previndex+1];
						*prevNode = ind + 17 + sizeWanted;
						*currllr = *myblock[ind + 8 + 1];

					}
					//if the node that was removed was the first node
					else{
						currllr = *myblock[ind + 8 + 1];
						short* linkedlist1 = &myblock[adjCurrArch];
			 			*linkedlist1 = nextblockIndex;

					}
					return &myblock[ind + 1+ 8];

				}
				break;
			}
			else{
				if(*nextNode == 0 ){
					//move to the next linked list because this one doesn't have right size
					return takeFromLL3(sizeWanted);
				}
				else{
					//size current is changed to index saved in the linked list short
					//ind is the current index which is now saved to nextnode
					//sizecurrent is 
					previndex = ind;
					sizecurrent = &myblock[*nextNode];
					ind = *nextNode;
					sizecurrent = &myblock[ind]
					nextnode = &myblock[ind + 9];

				}
			}
		}

	}

}




char * takeFromLL3 (int sizeWanted){
	//check if linked list is empty
	short* temp3 = myblock[adjCurrArch +currArch];
	if(*temp3 == 0){
		//recursively try to find the list with anything in it
		return takeFromLL4(sizeWanted);
	}
	//else there is actually something in this linked list
	else{
		short ind = *temp1;
		short* nextNode = &myblock[ind + 9];
		short* sizecurrent = &myblock[ind];
		short* prev;

		while(true){
			//found the one that would be able to fit the required size
			if(*sizecurrent >= sizeWanted){
				//have to either split the current linked list or give it back
				if(*sizecurrent> sizeWanted){
					char allo = 'a';
					myblock[ind+currArch] = allo;
					short sizer = *sizecurrent - sizeWanted;
					*sizecurrent = sizeWanted;
					

					//creating new block of whatever is left over
					char* charsizer = &myblock[ind + 17 + sizeWanted];
					short currsizer = (short*)charsize;
					*currsizer = currblocksize;
		
					//1 byte char stating whether the thing is allocated or not
					char allocatedr = 'u';
					&myblock[ind + 17 + sizeWanted + currArch] = allocatedr;
		
					//creating the node in the block for the linkeed list
					char* linkedlistr = &myblock[ind + 17 + sizeWanted+ currArch + 1];
					short currllr = (short*)linkedlist; 
					//if we didnt remove the front node
					if( *temp1 != ind){
						short * prevNode = &myblock[previndex+1];
						*prevNode = ind + 17 + sizeWanted;
						*currllr = *myblock[ind + 8 + 1];

					}
					//if the node that was removed was the first node
					else{
						currllr = *myblock[ind + 8 + 1];
						short* linkedlist1 = &myblock[adjCurrArch + currArch];
			 			*linkedlist1 = nextblockIndex;

					}
					return &myblock[ind+ 1+ 8];



				}
				//if the size matches perfectly
				else{
					char allo = 'a';
					myblock[ind + 8 ] = allo;

					if( *temp1 != ind){
						short * prevNode = &myblock[previndex+1];
						*prevNode = ind + 17 + sizeWanted;
						*currllr = *myblock[ind + 8 + 1];

					}
					//if the node that was removed was the first node
					else{
						currllr = *myblock[ind + 8 + 1];
						short* linkedlist1 = &myblock[adjCurrArch + currArch];
			 			*linkedlist1 = nextblockIndex;

					}
					return &myblock[ind + 1+ 8];

				}
				break;
			}
			else{
				if(*nextNode == 0 ){
					//move to the next linked list because this one doesn't have right size
					return takeFromLL4(sizeWanted);
				}
				else{
					//size current is changed to index saved in the linked list short
					//ind is the current index which is now saved to nextnode
					//sizecurrent is 
					previndex = ind;
					sizecurrent = &myblock[*nextNode];
					ind = *nextNode;
					sizecurrent = &myblock[ind]
					nextnode = &myblock[ind + 9];

				}
			}
		}

	}

}



char * takeFromLL4 ( int sizeWanted){
	//check if linked list is empty
	short* temp4 = myblock[adjCurrArch + currArch +currArch];
	if(*temp4 == 0){
		//recursively try to find the list with anything in it
		//since this is the last list and there is nothing bigger there must be no open spaces available
		return null;
	}
	//else there is actually something in this linked list
	else{
		short ind = *temp1;
		short* nextNode = &myblock[ind + 9];
		short* sizecurrent = &myblock[ind];
		short* prev;

		while(true){
			//found the one that would be able to fit the required size
			if(*sizecurrent >= sizeWanted){
				//have to either split the current linked list or give it back
				if(*sizecurrent> sizeWanted){
					char allo = 'a';
					myblock[ind+currArch] = allo;
					short sizer = *sizecurrent - sizeWanted;
					*sizecurrent = sizeWanted;
					

					//creating new block of whatever is left over
					char* charsizer = &myblock[ind + 17 + sizeWanted];
					short currsizer = (short*)charsize;
					*currsizer = currblocksize;
		
					//1 byte char stating whether the thing is allocated or not
					char allocatedr = 'u';
					&myblock[ind + 17 + sizeWanted + currArch] = allocatedr;
		
					//creating the node in the block for the linkeed list
					char* linkedlistr = &myblock[ind + 17 + sizeWanted+ currArch + 1];
					short currllr = (short*)linkedlist; 
					//if we didnt remove the front node
					if( *temp1 != ind){
						short * prevNode = &myblock[previndex+1];
						*prevNode = ind + 17 + sizeWanted;
						*currllr = *myblock[ind + 8 + 1];

					}
					//if the node that was removed was the first node
					else{
						currllr = *myblock[ind + 8 + 1];
						short* linkedlist1 = &myblock[adjCurrArch + currArch +currArch];
			 			*linkedlist1 = nextblockIndex;

					}
					return &myblock[ind+ 1+ 8];



				}
				//if the size matches perfectly
				else{
					char allo = 'a';
					myblock[ind + 8 ] = allo;

					if( *temp1 != ind){
						short * prevNode = &myblock[previndex+1];
						*prevNode = ind + 17 + sizeWanted;
						*currllr = *myblock[ind + 8 + 1];

					}
					//if the node that was removed was the first node
					else{
						currllr = *myblock[ind + 8 + 1];
						short* linkedlist1 = &myblock[adjCurrArch + currArch +currArch];
			 			*linkedlist1 = nextblockIndex;

					}
					return &myblock[ind + 1+ 8];

				}
				break;
			}
			else{
				if(*nextNode == 0 ){
					//nothing bigger avaible so returning null
					return null;
				}
				else{
					//size current is changed to index saved in the linked list short
					//ind is the current index which is now saved to nextnode
					//sizecurrent is 
					previndex = ind;
					sizecurrent = &myblock[*nextNode];
					ind = *nextNode;
					sizecurrent = &myblock[ind]
					nextnode = &myblock[ind + 9];

				}
			}
		}

	}

}


//*********MALLOC FUNCTION**********
//The meat and bones of this program, the malloc function
char* myMalloc(int sizeGiven){
	int size = sizeGiven;

//person tries to malloc the entire array
if(size >= 5000){ printf("You cannot malloc more then 50000\n"); return null;}

char * returnPointer;
	//checking if the array already has the meta data associated with it
	//Meta Dat already exist, this isn't the first time malloc is used
	if(intialized == 1){
		printf("Malloc is being reused\n");

		//minimum size allowed for malloc is 30, will return atleast 30 no matter 
		//will set the block size to be 13 or 21 so that metadata for 64 bit or 32 bit will equal 30 bytes
		if(size < 30){
			if(currArch = 8){
				size  = 13;}
			else{
				size = 21;
			}
		}

		//check linked list to see where the fit is 

		if(size<= 1250){
			//send to helper function
			returnPointer = takeFromLL1(size);
			}
		}
		if(size <= 2500 && size >= 1251){
			//send to helper function
			returnPointer = takeFromLL2(size);
			}

		}
		if(size <= 3750 && size >= 2501){
			//send to helper function
			returnPointer = takeFromLL3(size);
			}

		}		
		if(size <= 5000 && size >= 3751){
			//send to helper function
			returnPointer = takeFromLL4(size);
			}

		}

		


	}

	//This is the first time malloc is being used
	else{
		printf("Malloc is being run for the first time\n");

		
		//Using Segregation Fit 
		//ll1, ll2, ll3 , ll4 are linked list pointing to diffrent block sizes
		//ll1 =   30 - 1250 bytes
		//ll2 = 1251 - 2500 bytes
		//ll3 = 2501 - 3750 bytes
		//ll4 = 3570 - 4984 bytes
		//ll4 assumes that 8 bytes are used for ll meta data and 8 bytes for 1st block meta data
		//
		//----------------------------------------------------------------
		//|             |                |               |               |
		//|  30 - 1250  |   1251 - 2500  |  2501 = 3750  |  3570 - 4984  |
		//|    bytes    |      bytes     |      bytes    |     bytes     |
		//|             |                |               |               |
		//----------------------------------------------------------------
		short ll1;
		short ll2;
		short ll3;
		short ll4;
		//will make sure that the program runs on both 64 bit and 32 bit arch by setting byte by checking si			ze of *char 
		//int currArch = sizeof(short*);
		//int adjCurrArch = currArch -1; adjusting for odd indexes becuase 0 is a index
		char * p1 = &myblock[0];
		char * p2 = &myblock[adjCurrArch];
		char * p3 = &myblock[adjCurrArch + currArch ];
		char * p4 = &myblock[adjCurrArch + currArch + currArch ];
		ll1 = (short*)p1;
		ll2 = (short*)p2;
		ll3 = (short*)p3;
		ll4 = (short*)p4;
		*ll1 = 0;
		*ll2 = 0;
		*ll3 = 0;
		*ll4 = 0;


		
		
				
		//minimum size allowed for malloc is 30, will return atleast 30 no matter 
		//will set the block size to be 13 or 21 so that metadata for 64 bit or 32 bit will equal 30 bytes
		if(size < 30){
			if(currArch = 8){
				size  = 13;}
			else{
				size = 21;
			}
		}
		

		//setting the size for the first malloc block to requested
		char* charsize = &myblock[adjCurrArch + 3(currArch)];
		short currsize = (short*)charsize;
		*currsize = size;
		
		//1 byte char stating whether the thing is allocated or not
		char allocated = 'a';
		&myblock[adjCurrArch + 4(currArch)] = allocated;
		
		//creating the node in the block for the linkeed list
		char* linkedlist = &myblock[adjCurrArch + 4(currArch) + 1];
		short currll = (short*)linkedlist;
		*currll = 0;
		//setting the return address  
		returnPointer = &myblock[adjCurrArch + 5(currArch) + 1];
		printf("Return Address is: %p\n", &returnPointer);
		
		//since this is the first block to be allocated we can assume that it will automatically be added to the front of whatever linked list it corresponds to 
		
		//putting into diffrent linked list
		//nextblock index calculates the index at which the next unallocated block is 	
		short nextblockIndex = 1 + constantMem + 2(currArch) + size;
		//currblocksize finds the size of the new block that is unallocated
		short currblocksize = 5000 - (nextblockIndex + 2(currArch) +1); 
		//finding in which linked list the new block fits
		if(currblocksize<= 1250){
			short* linkedlist1 = &myblock[0];
			 *linkedlist1 = nextblockIndex;
			
		}
		if(currblocksize <= 2500 && size >= 1251){
			short* linkedlist2 = &myblock[adjCurrArch];
			*linkedlist2 = nextblockIndex;
		}
		if(currblocksize <= 3750 && size >= 2501){
			short* linkedlist3 = &myblock[adjCurrArch + currArch];
			*linkedlist3 = nextblockIndex;
		}		
		if(currblocksize <= 5000 && size >= 3751){
			short* linkedlist4 = &myblock[adjCurrArch + currArch + currArch];
			*linkedlist4 = nextblockIndex;
		}
		
		//since we have now created pointer to the first index of the now new spot we can now create block from it
		//Creating the block

        //setting the size for the first malloc block to requested
		char* charsizer = &myblock[nextblockIndex];
		short currsizer = (short*)charsize;
		*currsizer = currblocksize;
		
		//1 byte char stating whether the thing is allocated or not
		char allocatedr = 'u';
		&myblock[nextblockIndex + currArch] = allocatedr;
		
		//creating the node in the block for the linkeed list
		char* linkedlistr = &myblock[nextblockIndex + currArch + 1];
		short currllr = (short*)linkedlistr; 
		*currllr = 0;                                                                  


		
		//changing the intialised int so that we don't come to else statement again
		intialized = 1;
		return returnPointer; 
	}

}

//********FREE FUNCTION************
//The free function, to free up memory allocated by malloc
void free(char* pointer){

}







