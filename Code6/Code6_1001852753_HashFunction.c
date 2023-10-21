/* HashFunction for Coding Assignment 6
Name: Mary-Rose Tracy 
ID#:1001852753
*/
//NOTE: I'm gonna put all of the includes so when I make my coding assignment then I can have it done.
#include <stdlib.h> //given Code
#include <stdio.h> 
#include <string.h>
#include <time.h>
#include <math.h>
#define HASHTABLESIZE 10 //given Code

int MyHashFunction (char OfTheName[]) //pass in value being used in hash
{
	int Length= strlen(OfTheName); //The instructions are giving me that I need to use a for loop.
	int value=0; //we need return value so let's do value
	for (int i=0; i<Length;i++)
	{
		value = value + OfTheName[i];
        return value % HASHTABLESIZE;
	}
}

int main()
{
	char HashValue[20]; //in given code
	printf("Enter Value");
	scanf("%s",HashValue); //no &
	printf("The hash value for %s is %d\n",HashValue ,MyHashFunction(HashValue));
	return 0;
}