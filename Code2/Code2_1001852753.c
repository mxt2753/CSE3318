/* Coding Assignment 2 
Name: Mary-Rose Tracy 
ID#:1001852753
*/
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>
#include <math.h>
//Removed max length because i was confusing myself
//NOTES: Okay so I'm gonna start over and go step by step because I'm confusing myself with my logic from the previous coding assignment 1 
void InsertionSort(int **AP, int BufferCount) //void InsertionSort(int arr[], int n)
{
    int i, j, Key; //from insertion sort examples
    for (i = 1; i < BufferCount; i++) //did Buffercount to be more specific
    {
        Key = (*AP)[i];
        j = i - 1;
        while (j >= 0 && (*AP)[j] > Key) //create a while lop
        {
            (*AP)[j + 1] = (*AP)[j];
            j = j - 1;
        }
        (*AP)[j + 1] = Key;
    }
}
//Step 6 & 5: Deleted Free CL, & Deleted the linked list struct along with the code to find the node & such.
//Step 4. I completely changed main and read in this assignment because i confused myself & wasn't working
int ReadFileIntoArray(int argc , char *argv[] , int **AP) //ReadFileIntoCL NODE **LinkedListHead
{
    //changed buffer = BufferSum (Buffer of Sum), ANum  (A Number)just so I can distinguish more clearly. Along with having Buffer Count
    int BufferSum, ANum, i = 0; //initialized BufferSum, BufferCount on two different lines just so I can see the different aspects.
    int BufferCount = 0;
    char ChOfBuffer[300] = {0}; //300 characters sounds good of ChOfBuffer means char of buffer
    FILE *FilePoint = NULL; //instead of fp, I did FilePoint
    FilePoint = fopen(argv[1], "r"); //from lecture slide only just renamed fp =FilePoint
    if (argc < 2)      //or would it be two or another num?
    {
        printf("File must be provided on command line...exiting");
        exit(0);
    }
    while(fgets(ChOfBuffer,300, FilePoint) != NULL)
    {
        BufferCount++;
    }
    *AP = malloc(BufferCount* sizeof(int)); //From the Lecture slides, just changed buffer
    fseek(FilePoint, 0, SEEK_SET); //SEEK_SET = "moves file pointer position to the beginning of the file"
    while(fgets(ChOfBuffer, 300,FilePoint)!= NULL)
    {
        int LengthOInt = strlen(ChOfBuffer);
        if(ChOfBuffer[LengthOInt - 1] == '\n')
        {
            ChOfBuffer[LengthOInt - 1] = 0;
        }
        ANum = atoi(ChOfBuffer);
        BufferSum = BufferSum + ANum;
        (*AP)[i] = ANum;
        i++;
    }
    InsertionSort(AP, BufferCount);
    return BufferCount;
}
void PrintArray(int *AP, int BufferCount) //make a function to essentially to print the array.
{
    int i = 0;
    for(i = 0; i < BufferCount; i++)
    {
        printf("%d\n", (AP)[i]);
    }
}
int main(int argc, char  *argv[])
{
    clock_t start, end; //from coding assignment 1/
    int BufferCount = 0;
    int *AP = 0;
    BufferCount = ReadFileIntoArray(argc, argv, &AP);
    PrintArray(AP, BufferCount);
    start=clock();
    PrintArray(AP, BufferCount);
    end=clock();
    #ifdef PRINTARRAY
    printf("\nProcessed %d records\n", BufferCount);
    printf("\nInsertion Sort Tics = %ld\n", end-start);
    #else 
    printf("\nInsertion Sort = %ld Tics\n", end-start);
    #endif
    return 0;
}
