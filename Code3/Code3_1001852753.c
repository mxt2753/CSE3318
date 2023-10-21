/* Coding Assignment 3
Name: Mary-Rose Tracy 
ID#:1001852753
*/
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>
#include <math.h> //#define MAXLENGTH 50 //Don't think I'll need it, but 

void InsertionSort(int **AP, int Count) //void InsertionSort(int arr[], int n), AP= Argument pointer
{
    int i, j, Key; //from insertion sort examples
    for (i = 1; i < Count; i++) //did Buffercount to be more specific
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
//Step 6 & 5: Deleted Free CL, & Deleted the linked list struct along with the code to find the node & such. (Step 4. I completely changed main and read in this assignment because i confused myself & wasn't working)
int ReadFileIntoArray(int argc, char *argv[], int **AP) //FilePoint or fp
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
    return BufferCount;//InsertionSort(AP, BufferCount) This messed me up ;
}

void Merge(int arr[], int l, int m, int r) //Combo from slides, logic, & compared to other mergesort funct on the internet, like the instructions say
{
    int i, j, k;
    int Num1 = m - l + 1;
    int Num2 = r - m;
    int L[Num1], R[Num2];
    for (i = 0; i < Num1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < Num2; j++)
        R[j] = arr[m + 1 + j];
    i = 0; 
    j = 0; 
    k = l; 
    while (i < Num1 && j < Num2)
    {
        if (L[i] <= R[j]) 
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < Num1) 
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < Num2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void MergeSort(int arr[], int l, int r) //combo from slides, logic, & compared other functions on the internet like the instructions say
{
    if (l < r) 
    {
        int m = l + (r - l) / 2;
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
        Merge(arr, l, m, r);
    }
}
void PrintArray(int *AP , int count) //Think it's a different count than Count 
{
    int i;
    for (i=0; i<count;i++)
    {
        printf("%d\n",AP[i] );
    }
    printf("\n");
}
int main(int argc, char *argv[])
{
    int *AP = 0; //Declare array pointer  (int BufferCount = 0;below but didn't need it)
    int Count = ReadFileIntoArray( argc ,argv ,&AP);
    clock_t Start, End; //did campitalized 
    ReadFileIntoArray(argc ,argv ,&AP); //Call function to read file into array 
    #ifdef PRINTARRAY//#ifdef PRINTARRAY 
    PrintArray(AP, Count);//Print the array (should be unsorted) 
    #endif//#endif
    Start=clock();//Start the clock for Merge Sort 
    MergeSort(AP, 0, Count -1); //Call Merge Sort (clock_t merge= End - Start; but didn't need it)
    End=clock(); //Stop the clock for Merge Sort 
    clock_t Merge= End - Start;
    #ifdef PRINTARRAY//#ifdef PRINTARRAY
    PrintArray(AP , Count);//Print the array (should be sorted) 
    #endif//#endif
    free(AP); //Free the malloced pointer 
    int array_count = ReadFileIntoArray( argc , argv ,&AP );//Call function to read file into array
    #ifdef PRINTARRAY//#ifdef PRINTARRAY 
    PrintArray(AP , Count);//Print the array (should be unsorted) 
    #endif//#endif
    Start=clock();//Start the clock for Insertion Sort 
    InsertionSort(&AP, Count);//Call Insertion Sort 
    End=clock();//Stop the clock for Insertion Sort 
    #ifdef PRINTARRAY //#ifdef PRINTARRAY
    PrintArray(AP, Count); //Print the array (should be sorted) 
    #endif //#endif
    free(AP); //Free the malloced pointer
    printf("Processed %d records", Count); //print how many records were in the file/array 
    printf("\nMerge Sort     = %ld ", Merge); //print how many tics were used by Merge Sort
    printf("\nInsertion Sort = %ld\n", End-Start); //Print how many tics were used by Insertion Sort 
    return 0;
}
