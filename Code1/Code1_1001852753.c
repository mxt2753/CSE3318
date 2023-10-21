/* Coding Assignment 1 
Name: Mary-Rose Tracy 
ID#:1001852753
*/
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>
#define The_Max_Length 120 //120 characters, because the output is gonna be alot of characters, So 120 should be good 
//1. Create a function to read the file
typedef struct node //So here we are trying to set the structs for later. Which we are suppose to * because of the next pointer. 
{
	int number;
	struct node* nextpointer; //Notice that we are only gonna do struct node but the function would only be referenced as NODE after this 
}
NODE;
//Create a function to add a node the linked list
//1.5 call a function to add nodes to the linked list
void AddtoLinkedList(int number, NODE **LinkedListHead) //Remember linkedlisthead & llh don't mix them up 
{
	//passes the head of the linked list , then trvaerses until an empty node is found & need a way to define the head
	NODE* newNode; 
	newNode = malloc(sizeof(NODE));
	newNode->number = number;   //So we have to make the newnode go through the number in order to store it
	newNode->nextpointer=NULL; 
	NODE *tempp;
	tempp = malloc(sizeof(NODE));
	// once you have stored the value in the node , you need to traverse until you find an empty node 
	//Pretty sure it's talking about temporary_num= linkedlisthead W/ a pointer
	tempp=*LinkedListHead;
	// if you are in the head , aka you have nothing in the nextpointer
	//So the tempp == to NUll if else statement
	if (tempp == NULL)
	{
		*LinkedListHead = newNode;
	}
	//This is where we do the else with Traverse untill we get the head, We need to add the linkedlist
	else
	{
		while (tempp->nextpointer!= NULL)
		{
			tempp = tempp-> nextpointer;
		}
		tempp->nextpointer = newNode;
		newNode ->nextpointer = NULL;
	}
}
//3. Create a function to print the linked list
void PrintLL(NODE *LinkedListHead) 
{
	NODE *tempp; //Tempp = Temporary npointer 
	tempp=LinkedListHead;
	
	int BufferC=0; //nodeC= Node of count
	int BufferS=0; //NodeS=Node of sum
	while (tempp!=NULL) // on the paper if def PRINT 
	{
		//tempp= *LinkedListHead;
		BufferC++;
		BufferS = BufferS + tempp->number;

		//*LinkedListHead=(*LinkedListHead)->nextpointer
		#ifdef PRINT
        printf("\n %p %d %p\n", tempp, tempp->number, tempp->nextpointer);
        #endif
		tempp=tempp->nextpointer; 
	}
	printf("\n%d records were read for a total sum of %d \n", BufferC , BufferS );
}
//4. Create a function to free the linked list node memory 
void FreeLL(NODE **LinkedListHead) 
{ 
	NODE *tempp;
	tempp = malloc(sizeof(NODE));

	int NodeC=0; //nodeC= Node of count
	int NodeS=0; //NodeS=Node of sum

	while (*LinkedListHead!=NULL)
	{
		tempp= *LinkedListHead;

		NodeC++;
		NodeS = NodeS + tempp->number;

		*LinkedListHead=(*LinkedListHead)->nextpointer;

		#ifdef PRINT
        printf("\nFreeing %p %d %p\n", tempp, tempp->number, tempp->nextpointer); 
        #endif
		free(tempp);	//we have to free the linked list so it doesn't mess up 
	}
	printf("\n%d nodes were deleted for a total sum of %d \n", NodeC ,NodeS );
}
//2. Create a function to Read a node the linked list
void ReadFileIntoLL(int argc , char *argv[] , NODE **LinkedListHead) 
{
	int BufferC=0; //Buffer of count
	int BufferS=0; //Buffer of Sum 

	FILE *FileP; // file ppointer or fp for short
	FileP=fopen (argv[1], "r");

	if (FileP==NULL)
	{
		printf("Error while opening the file \n");
		exit(EXIT_FAILURE);
	}

	char buffer[The_Max_Length]={0}; // Need to store each value for a char which is called buffer

	while (fgets(buffer,The_Max_Length,FileP)) //+ to linked list with the fgets
	{
		BufferC++;
		BufferS=BufferS+atoi(buffer);	
		AddtoLinkedList(atoi(buffer),  LinkedListHead );
	}

	printf("\n%d records were read for a total sum of %d\n",BufferC,BufferS );
}
//5. Main()
//Okay I'm gonna delete the instruction because I was confusing my self
int main(int argc, char  *argv[])
{
	if (argc==1) //We needargc to equal to argc
	{
		printf("File must be provided on command line...exiting\n");
		return 0;
	}
	clock_t start,end; //need long int  aka %ld because the clock_t = is long. so it's bigger & set linkedlisthead to null
	NODE *LinkedListHead = NULL; 
	
	start=clock(); //the instruction's just say to call clock not necessarily put something in those parenthesis
	ReadFileIntoLL(argc,argv, &LinkedListHead);
	end=clock();
	printf("\n%ld tics to write the file into the linked list\n", end-start); //We have to put end minus start for the final printable thing we see.

    #ifdef PRINT
	start=clock();
	PrintLL(LinkedListHead);
	end=clock();
	printf("\n%ld tics to print the linked list\n", end-start);
	#endif

	start=clock();
	FreeLL(&LinkedListHead);
	end=clock();
	printf("\n%ld tics to free the linked list\n", end-start);

	return 0;
}
