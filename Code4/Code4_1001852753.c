/* Coding Assignment 4
Name: Mary-Rose Tracy 
ID#:1001852753
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MAXLENGTH 50

void swap(int *SwapA , int *SwapB) //need swap from slides 
{
    int temp= *SwapA;
    *SwapA= *SwapB;
    *SwapB= temp;
}
int partition(int AreaP[] , int low , int high) //now lets do partition
{
    #if QSM //from coding assignment instructions, NOTE: changes it a little bit to understand it beeter
    int middle = (high+low)/2;
    swap(&AreaP[middle], &AreaP[high]);
    #elif QSRND
    int random= (rand() % (high-low+1)) + low;
    swap(&AreaP[random], &AreaP[high]);
    #endif
    int Pivot= AreaP[high]; //Areap meaning AP
    int i, j=0;
    i= low-1;
    for (j=low; j<high;j++)
    {
        if (AreaP[j]<Pivot)
        {
            i++;
            swap(&AreaP[i], &AreaP[j]);
        }
    }
    swap(&AreaP[i+1], &AreaP[high]);
    return (i+1); //correct
}
void QuickSort(int AreaP[] , int low , int high) //quicksort funct
{
    if(low<high)
    {
        int Index = partition(AreaP , low , high); //I think we next have to do a index -1 & then index +1
        QuickSort(AreaP, low, Index-1); //Index -1
        QuickSort(AreaP, Index+1, high); //Index +1
    }
}
int ReadFileIntoArray(int argc, char *argv[], int **AreaP) //changed it a little bit to understand it 
{
    FILE *FilePoint; //aka fp
    FilePoint = fopen (argv[1], "r"); //argv[1] the other variable wasn't working
    int BufferSum, ANum, i = 0; 
    int BufferCounter=0;
    char ChOfBuffer[MAXLENGTH]={0}; // we don't need to initialize a certain number we can just do a define and set the MAXLENGTH to a ceratin number to easily change it
    if (argc<2) //this doesn't technically print, just gonna leave it here because its sim to coding assingment 1 Filepoint does it's job, and that's what the professor told me to do. 
    {
        printf("File must be provided on command line... exiting\n");
        exit(0);
    }
    if (FilePoint==NULL)
    {
        printf("Error while opening the file \n");
        exit(0);
    }
    while (fgets(ChOfBuffer, MAXLENGTH, FilePoint))
    {
        BufferCounter++;
    }
    *AreaP =  malloc (BufferCounter * sizeof(int));
    fseek(FilePoint, 0, 0);
    int Count =0;
    while(fgets(ChOfBuffer , MAXLENGTH , FilePoint))
    {
        (*AreaP)[Count]= atoi(ChOfBuffer);
        Count++;
    }
    fclose(FilePoint);
    return Count; //Count-1 didn't work
}
void PrintArray(int *AreaP , int count) // need print array funct
{
    int i;
    for (i=0; i<count;i++)
    {
        printf("%d\n",AreaP[i] );
    }
    printf("\n");
}
int main(int argc, char *argv[])
{
    int NRound; //int *AreaP = NULL; //int Count = ReadFileIntoArray(argc, argv, &AreaP); didn't work
    if(argc < 3 ) //if argv is not specifiec it does 10 and if it's not there then it exits.
    {
        printf("Number of runs not specified on command line... defaulting to 10\n"); 
        NRound=10;
    }
    else
    {
        NRound = atoi(argv[2]);
    }
    int *AreaP = NULL;
    long int Average =0;//int Count = ReadFileIntoArray(); wasn't working, also we need to initialize mroe variables here to so that's why i separated them
    int i;
    int Count = 0;
    for (i=0;i<NRound; i++) //let's do a loop
    {
        Count = ReadFileIntoArray(argc, argv, &AreaP);
        #ifdef PRINTARRAY
        PrintArray(AreaP , Count); //Count -1 wasn't working 
        #endif
        clock_t Start , End; //capitalized to focus on that 
        Start = clock();
        QuickSort(AreaP, 0 ,Count-1); //Count -1 wasn't working 
        End = clock();
        printf("Run  %d complete : %lu tics \n" , i+1 , End-Start); //comment needs to be within the loop
        Average=Average+(End-Start);
        #ifdef PRINTARRAY
        PrintArray(AreaP , Count); //Count -1 wasn't working
        #endif
        free(AreaP); //need to free AP or AreaP
    }
    printf("The average run time for %d runs is %lu\n", NRound , Average/NRound); //let's put the printf statements out of the loop so we can print them no matter what
    printf("\nProcessed %d records\n", Count);
    return 0;
}


