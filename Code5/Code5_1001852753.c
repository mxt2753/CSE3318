/* Coding Assignment 5
Name: Mary-Rose Tracy 
ID#:1001852753
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAXNUM 11 // 6 by 5 so lets make it 11.
#define DBUFFER 105 //Define buffer
#define MAXLENGTH 30 //because like I'm think we need alot of room. so max max length is gonna be 30.

typedef struct
{
    int index; //or we could call it i
    char label[6];//6 in class
    int distance; //used in other code from assignment
    int previous; //used in other code from assignment
    int visited; //used in other code from assignment
}
Vertex;
Vertex VertexArray[MAXNUM];
void AddTheVertex(Vertex VertexArray[] , int *VertexOCount , char StringOfName[]) //VertexOCount=VertexOfCount 
{
    VertexArray[(*VertexOCount)].index = *VertexOCount;
    strcpy(VertexArray[(*VertexOCount)].label, StringOfName);
    VertexArray[(*VertexOCount)].distance=INT_MAX; //INT_MAX is a function
    VertexArray[(*VertexOCount)].previous=-1;
    VertexArray[(*VertexOCount)].visited=0;
    (*VertexOCount)++;
}
void AddTheEdge(int Start, int End, int TheValue, int AdjMatrix[][MAXNUM]) //AdjMatrix= Adjacency Matrix
{
    AdjMatrix[Start][End]=TheValue;
}
void ClearingOfarray(int A[])
{
    int i=0;
    for (i=0; i<MAXNUM;i++)
    {
        A[i]=0;
    }
}
int GetIndex(char A[], Vertex VertexArray[], int VertexOCount, int *index)
{
    int i=0;
    for(i=0;i<VertexOCount;i++)
    {
        if(strcmp(A, VertexArray[i].label)==0)
        {
            *index=VertexArray[i].index;
        }
    }
}
int main(int argc, char const *argv[])
{
    int AdjMatrix[MAXNUM][MAXNUM]={};
    int j=0;
    int i=0;
    for(i=0;i<MAXNUM;i++)
    {
        for(j=0;j<MAXNUM;j++)
        {
            AdjMatrix[i][j]=-1;
        }
    }
    FILE *FileP;
    FileP = fopen(argv[1], "r");
    char Line[MAXNUM][DBUFFER];
    int VertexCount=0;
    int ArrayToStoreVertex[MAXNUM];
    int ArrayOCount=0;
    int VertexOCount=0; //DIFFERENT FROM VERTEXCOUNT
    char *TOK;
    while(fgets(Line[VertexCount],DBUFFER,FileP)) //let's store the V in correlation to each Vertex. Like the array is gonna store the letters & numbers in different parts of the matrix.
    {
        ClearingOfarray(ArrayToStoreVertex);
        ArrayOCount=0;
        TOK = strtok(Line[VertexCount],",");
        AddTheVertex(VertexArray, &VertexOCount, TOK );
        while(TOK!=NULL)
        {
            TOK = strtok(NULL , ",");
            if(TOK!=NULL)
            {
                ArrayToStoreVertex[ArrayOCount++]= atoi(TOK); //We need to get the value of the array
            }
        }
        for(i=0;i<ArrayOCount;i=i+2)
        {
            AddTheEdge(VertexCount, ArrayToStoreVertex[i], ArrayToStoreVertex[i+1],  AdjMatrix );//This code changes the weights & the edges to get the adjacency matrix.
        }
        VertexCount++;
    }
    fclose(FileP); //Now let's print the Adjacency matrix
    #ifdef PRINTIT //c
    printf("\n"); //c
    for(i=0;i<VertexCount;i++) //line_count = vertex count & c
    {
        for(j=0;j<VertexCount;j++) //check also LISTEN I copied what was on the pdf for the coding assignment for this part, but it looks like it's soppose to be indented like this??
            printf("%5d\t",AdjMatrix[i][j]); //c
        printf("\n"); //IT LOOKS LIKE It's SUPPOSE TO BE LIKE THIS IN THE CODING ASSINGMENT IN TERMS OF INDENTION!!!
    }
    #endif //c
    char InputStartOVertex[MAXLENGTH]; //let's run Djikstra we need ALOT Of variables to initialize
    char InputEndOVertex[MAXLENGTH];
    printf("\nWhat is the starting vertex? ");
    scanf(" %s" , InputStartOVertex);
    int SourceOfIn = 0;
    GetIndex(InputStartOVertex, VertexArray, VertexOCount, &SourceOfIn); //int GetIndex= (InputStartOVertex, VertexArray, VertexOCount,&SourceOfIn);
    int StartVertex=SourceOfIn;
    int CurrentVertex=StartVertex;
    VertexArray[StartVertex].distance=0;
    VertexArray[StartVertex].previous=-1;
    VertexArray[StartVertex].visited = 1;
    int x=0;
    int DirofU;
    int DirofV;
    int CountofUV;
    int SmallestVertexIndex=0;//Now let's make the loopy loop
    for(x=0;x<VertexOCount-1;x++)
    {
        for( i=0; i<VertexOCount;i++)
        {
            if(AdjMatrix[CurrentVertex][i]!=-1 && !VertexArray[i].visited) //if current vertex and i are neighbours and i has not been visited.
            {
                DirofU=VertexArray[CurrentVertex].distance;
                CountofUV=AdjMatrix[CurrentVertex][i];
                DirofV=VertexArray[i].distance; //Let's make a function that will see if the condition is good then it changes it.
                if(DirofU+CountofUV<DirofV)
                {
                    DirofV=DirofU+CountofUV;
                    VertexArray[i].distance=DirofV;
                    VertexArray[i].previous=CurrentVertex;
                }
            }
        }
        SmallestVertexIndex=-1; //r
        int SmalestVertex=INT_MAX; //r NOT THE SAME AS SMALLESTVERTEX
        for (i=0;i<VertexOCount;i++)
        {
            for(j=0;j<VertexOCount;j++)
            {
                if(!VertexArray[j].visited)
                {
                    if(VertexArray[j].distance <SmalestVertex)
                    {
                        SmalestVertex=VertexArray[j].distance;
                        SmallestVertexIndex=j;
                    }	
                }
            }
        }
        CurrentVertex=SmallestVertexIndex;
        VertexArray[CurrentVertex].visited=1;
    }
    #ifdef PRINTIT
    printf("\n\nI\tL\tD\tP\tV\n"); //I would've done this a little more differently, but okay c
    for(i=0;i<VertexOCount;i++) //c
    {
        printf("%d\t%s\t%d\t%d\t%d\n", i,  VertexArray[i].label , VertexArray[i].distance , VertexArray[i].previous , VertexArray[i].visited); // I would've said VertexArray[i].index,for i but it looks like it doesn't matter.
    }
    printf("\n");
    #endif //int EndOfInput = 0; didn't work
    printf("\nWhat is the destination vertex? ");
    scanf(" %s", InputEndOVertex);
    int EndOfInput = 0;
    GetIndex(InputEndOVertex, VertexArray, VertexOCount, &EndOfInput); //GetIndex(InputStartOVertex, VertexArray, VertexOCount, &EndOfInput); || //int EndOfInput = GetIndex(InputEndOVertex , VertexArray , VertexOCount);
    if(VertexArray[EndOfInput].previous==-1)
    {
        printf("There is no path from %s to %s\n" , InputStartOVertex , InputEndOVertex );	
    }
    else
    {
        int TotOfDistance=-1; //okay we need to ask for the source of the graph
        int PrevOIndex=-1;
        char RouteOf[MAXNUM][MAXLENGTH];
        int IntCount=0;
        while (IntCount<VertexOCount && EndOfInput!=VertexArray[IntCount].index)
        {
            IntCount++;
        }
        if(IntCount==VertexOCount)
        {
            printf("The vertex is not in the graph\n");
        }
        else
        {
            IntCount=0;
            strcpy(RouteOf[IntCount++] , VertexArray[EndOfInput].label);
            TotOfDistance=VertexArray[EndOfInput].distance;
            PrevOIndex=VertexArray[EndOfInput].previous;
            while(VertexArray[PrevOIndex].index != SourceOfIn)
            {
                strcpy(RouteOf[IntCount++] , VertexArray[PrevOIndex].label);
                PrevOIndex=VertexArray[PrevOIndex].previous;
            }
        }
        printf("The path from %s to %s is %s->" , InputStartOVertex , InputEndOVertex , InputStartOVertex);
        for(i=IntCount-1;i>=0;i--)
        {
            if(i!=0)
            {
                printf("%s->",RouteOf[i]);
            }
            else if (i==0)
            {
                printf("%s",RouteOf[i] );
            }
        }
        printf(" and has a length of %d\n", TotOfDistance);
    }
    return 0;
}

