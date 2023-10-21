/* Coding Assignment 6 
Name: Mary-Rose Tracy 
ID#:1001852753
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define HASHTABLESIZE 30 //for test 2 30 change to 60 for test 3: change to 15 Test 4: 30 Test 5: change to 1
typedef struct MyFavoriteBands
{
    char *NameofBands;
    float HeightOfMainSingerInImperial;
    char *TopRankingSong; //For TopRankingSong Took into consideration spotify and Youtube.
    int MonthlyListenersOnSpotify;
    int SpotifyFollowers;
    char *TheirGenre; //the overall genre that their music label categorizes them.
    char Gender;
    struct MyFavoriteBands *next_ptr;
}
MYFAVORITEBANDS;
int CalculateHashIndex(char *key)
{
    int HashIndex = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        HashIndex += key[i];
    }
    return HashIndex %= HASHTABLESIZE; 
}
void AddNode(MYFAVORITEBANDS *NewNode, MYFAVORITEBANDS *FavBandData[])
{
    int HashIndex = CalculateHashIndex(NewNode->NameofBands); /* a linked list does not exist for this cell of the array */
    if (FavBandData[HashIndex] == NULL) 
    {
        #if PRINTINSERT //so we are entering the data & if the LL is nonexistent
        printf("\nInserting %s at index %d\n", NewNode->NameofBands, HashIndex);
        #endif
        FavBandData[HashIndex] = NewNode;
    }
    else   /* A Linked List is present at given index of Hash Table */ 
    {
        MYFAVORITEBANDS *TempPtr = FavBandData[HashIndex];
        while (TempPtr->next_ptr != NULL) 
        {
            TempPtr = TempPtr->next_ptr;
        }
        TempPtr->next_ptr = NewNode;
        #if PRINTINSERT
        printf("\nInserting %s at index %d\n", NewNode->NameofBands, HashIndex);
        #endif
    }
}
void FreeDynamicMemory(MYFAVORITEBANDS *FavBandData[])
{
    MYFAVORITEBANDS *TempPtr = NULL, *NextPtr = NULL;
    int i=0;
    for (i = 0; i < HASHTABLESIZE; i++)
    {
        TempPtr = FavBandData[i];
        if (TempPtr != NULL) 
        {
            while (TempPtr != NULL) 
            {
                free(TempPtr->NameofBands);
                free(TempPtr->TopRankingSong);
                free(TempPtr->TheirGenre);
                NextPtr = TempPtr->next_ptr;
                free(TempPtr);
                TempPtr = NextPtr;
            }	
        }
    }
}
int DeleteNode(MYFAVORITEBANDS *FavBandData[]) /* Remove an element from Hash Table */ 
{
    char LookupName[100] = {}; 
    int result = 0;
    printf("Enter the name of the band to delete from the database ");
    scanf("%s", LookupName);
    int HashIndex = CalculateHashIndex(LookupName); /* Get linked list at key in array */
    MYFAVORITEBANDS *TempPtr = FavBandData[HashIndex];
    MYFAVORITEBANDS *PrevPtr = NULL; /* This array index does not have a linked list; therefore, no keys */
    if (TempPtr == NULL) 
    {
        printf("\n\nBand %s does not exist in the database\n\n", LookupName);
        result = 0;
    }
    else 
    {
        while (TempPtr != NULL) //The node so it can be deleted
        {
            if (strcmp(TempPtr->NameofBands, LookupName) == 0)
            {
                if (TempPtr == FavBandData[HashIndex]) /* If the node being deleted is the head node */
                {
                    FavBandData[HashIndex] = TempPtr->next_ptr;/* The node the head was pointing at is now the head */
                    printf("\nBand %s has been deleted from the database\n\n", TempPtr->NameofBands);
                    free(TempPtr);
                    TempPtr = NULL;
                }
                else /* Found node to be deleted - node is not the head */
                {
                    PrevPtr->next_ptr = TempPtr->next_ptr;
                    printf("\nBand %s has been deleted from the database\n\n", TempPtr->NameofBands);
                    free(TempPtr);
                    TempPtr = NULL;
                }
                result = 1;
            }
            else /* this is not the node that needs to be deleted but save its info and move to the next node in the linked list  */
            {
                PrevPtr = TempPtr;
                TempPtr = TempPtr->next_ptr;
            }
        }
        if (result == 0)
        {
            printf("\n\nBand %s does not exist in the database\n\n", LookupName);
        }
    }
    return result;
}
void DisplayHashTable(MYFAVORITEBANDS *FavBandData[]) /* display the contents of the Hash Table */
{
    int i;
    MYFAVORITEBANDS *TempPtr = NULL;
    for (i = 0; i < HASHTABLESIZE; i++) 
    {
        TempPtr = FavBandData[i];
        printf("\nFavorite Band Database[%d]-", i);
        if (TempPtr != NULL) 
        {
            while (TempPtr != NULL)
            {
                printf("%s|", TempPtr->NameofBands);
                TempPtr = TempPtr->next_ptr;
            }
        }
    }
}
void ShowByLetter(MYFAVORITEBANDS *FavBandData[])
{
    int i;
    MYFAVORITEBANDS *TempPtr = NULL;
    char LookupLetter = 'A';
    printf("\n\nEnter a letter of the alphabet ");
    scanf(" %c", &LookupLetter);
    LookupLetter = toupper(LookupLetter);
    for (i = 0; i < HASHTABLESIZE; i++) 
    {
        TempPtr = FavBandData[i];
        if (TempPtr != NULL) 
        {
            while (TempPtr != NULL)
            {
                if (toupper(TempPtr->NameofBands[0]) == LookupLetter)
                {
                    printf("%s\n", TempPtr->NameofBands);
                }
                TempPtr = TempPtr->next_ptr;
            }
        }
    }
}
void ShowByName(MYFAVORITEBANDS *FavBandData[])
{
    MYFAVORITEBANDS *TempPtr = NULL;
    char HeightOfMainSingerInImperial[10] = {};
    char feet[10] = {};
    char inches[10] = {};
    char LookupName[100] = {};
    int FoundIt = 0;
    printf("\n\nEnter Band's name: ");
    fgets(LookupName , sizeof(LookupName), stdin);
    if(LookupName[0] == '\n')
    {
        LookupName[0] = '\0';
    }
    fgets(LookupName, sizeof(LookupName),stdin);
    if(LookupName[strlen(LookupName)-1] == '\n')
    {
        LookupName[strlen(LookupName)-1] = '\0';
    }
    printf("Name is %s \n",LookupName );
    #if TIMING
    clock_t start, end;
    start = clock();
    #endif
    for (int i = 0; i < HASHTABLESIZE; i++) 
    {
        TempPtr = FavBandData[i];
        if (TempPtr != NULL) 
        {
            while (TempPtr != NULL)
            {
                if (strcmp(TempPtr->NameofBands, LookupName) == 0)
                {
                    #if TIMING
                    end = clock();
                    printf("\n\nSearch took %ld tics\n\n", end-start);
                    #endif
                    FoundIt = 1;
                    printf("\n\n%s\n", TempPtr->NameofBands);
                    printf("Height\t\t");
                    sprintf(HeightOfMainSingerInImperial, "%.2f", TempPtr->HeightOfMainSingerInImperial); 
                    for (int i = 0; i < strlen(HeightOfMainSingerInImperial); i++)
                    {
                        if (HeightOfMainSingerInImperial[i] == '.')
                        {
                            printf("\' ");
                        }
                        else
                        {
                            printf("%c", HeightOfMainSingerInImperial[i]);
                        }
                    }
                    printf("\"\n");
                    printf("Best Song\t%s\n" , TempPtr->TopRankingSong);
                    printf("Spotify Monthly Listeners \t%d\n" , TempPtr->MonthlyListenersOnSpotify);
                    printf("Spotify Followers\t%d\n" , TempPtr->SpotifyFollowers);
                    printf("Genre\t%s\n" , TempPtr->TheirGenre);
                    printf("Gender\t\t%c\n", TempPtr->Gender);
                }
                TempPtr = TempPtr->next_ptr;
            }
        }
    }
    if (FoundIt == 0)
        printf("\n\nBand %s not found in Database\n\n", LookupName);
}
void AddNewBand(MYFAVORITEBANDS *FavBandData[]) 
{
    int HashIndex = 0;
    MYFAVORITEBANDS *NewNode; 
    char TempBuffer[100] = {}; 
    NewNode = malloc(sizeof(MYFAVORITEBANDS));
    NewNode->next_ptr = NULL;
    printf("\n\nEnter new Band's name ");
    scanf("%s", TempBuffer); //c
    NewNode->NameofBands = malloc(strlen(TempBuffer)*sizeof(char)+1); //c
    strcpy(NewNode->NameofBands, TempBuffer);
    printf("\n\nEnter %s's height as feet.inches ", NewNode->NameofBands);
    scanf("%f", &(NewNode->HeightOfMainSingerInImperial)); // Extra fgets to clear stdin
    fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
    printf("\n\nEnter %s's top ranking song ", NewNode->NameofBands); 
    fgets(TempBuffer, sizeof(TempBuffer)-1, stdin); 
    TempBuffer[strlen(TempBuffer)-1] = '\0';
    NewNode->TopRankingSong = malloc(strlen(TempBuffer)*sizeof(char)+1);
    strcpy(NewNode->TopRankingSong, TempBuffer);
    printf("\n\nEnter %s's the monthly listeners on spotify ", NewNode->NameofBands);
    scanf("%d", &(NewNode->MonthlyListenersOnSpotify));
    printf("\n\nEnter %s's spotify followers ", NewNode->NameofBands);
    scanf("%d", &(NewNode->SpotifyFollowers));
    printf("\n\nEnter %s's genre ", NewNode->NameofBands);
    scanf("%s", TempBuffer); //c
    NewNode->TheirGenre = malloc(strlen(TempBuffer)*sizeof(char)+1);
    strcpy(NewNode->TheirGenre,TempBuffer);
    printf("\n\nEnter %s's possible gender (M/F) ", NewNode->NameofBands);
    scanf(" %c", &(NewNode->Gender));
    NewNode->Gender = toupper(NewNode->Gender);
    AddNode(NewNode, FavBandData); 
}
int ReadFileIntoHashTable(int argc, char *argv[], MYFAVORITEBANDS *FavBandData[])
{
    FILE *FH = NULL;
    char FileLine[100] = {};
    char *token = NULL;
    int counter = 0;
    int HashIndex = 0;
    MYFAVORITEBANDS *NewNode; 
    if (argc > 1)
    {
        FH = fopen(argv[1], "r");
        if (FH == NULL)
        {
            perror("Exiting ");
            exit(0);
        }
        while (fgets(FileLine, sizeof(FileLine)-1, FH))
        {
            token = strtok(FileLine, "|");
            NewNode = malloc(sizeof(MYFAVORITEBANDS)); 
            NewNode->next_ptr = NULL;
            NewNode->NameofBands = malloc(strlen(token)*sizeof(char)+1);
            strcpy(NewNode->NameofBands, token);
            token = strtok(NULL, "|");
            NewNode->HeightOfMainSingerInImperial = atof(token);
            token = strtok (NULL , "|");
            NewNode->TopRankingSong= malloc(strlen(token)*sizeof(char)+1);
            strcpy(NewNode->TopRankingSong , token);
            token = strtok(NULL, "|");
            NewNode->MonthlyListenersOnSpotify = atol(token);
            token = strtok(NULL, "|");
            NewNode->SpotifyFollowers= atoi(token);//*token;
            token = strtok(NULL, "|");
            NewNode->TheirGenre = malloc(strlen(token)*sizeof(char)+1);
            strcpy(NewNode->TheirGenre, token);
            token = strtok(NULL , "|");
            NewNode->Gender = *token;
            AddNode(NewNode , FavBandData);
            counter++;
        }
    }
    else
    {
        printf("File must be provided on command line...exiting\n");
        exit(0);
    }
    fclose(FH);
    return counter;
}
int main(int argc, char *argv[]) 
{
    int MenuChoice = 0;
    int counter = 0;
    MYFAVORITEBANDS *FavBandData[HASHTABLESIZE] = {}; 
    enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
    counter = ReadFileIntoHashTable(argc, argv, FavBandData);
    do
    {
               printf("\n\nMy Favorite Bands Database Menu\n\n"
			   "1. Show all Bands in the database for a given letter\n" 
			   "2. Look up favorite band by name\n" 
			   "3. How many bands are in the database?\n" 
			   "4. Display the bands database\n"
			   "5. Add a new band\n" 
			   "6. Delete a bands from the database\n"
			   "7. Exit\n\n"
			   "Enter menu choice: ");
        scanf("%d", &MenuChoice);
        printf("\n\n");
        switch (MenuChoice)
        {	
            case SHOWBYLETTER:
                ShowByLetter(FavBandData); 
                break;
            case SHOWBYNAME:
                ShowByName(FavBandData); 
                break;
            case COUNT:
                printf("Your favorite band database contains %d of bands\n", counter); 
                break;
 			case DISPLAY:
                DisplayHashTable(FavBandData); 
                break;
            case ADD:
                AddNewBand(FavBandData);
                counter++;
                break;
            case DELETE:
                if (DeleteNode(FavBandData)) 
                {
                    counter--;
                }
                break;
            case EXIT:
                break;
            default : 
                printf("Invalid menu choice\n\n"); 
        }
    }
    while (MenuChoice != EXIT);
    FreeDynamicMemory(FavBandData); 
    return 0;
}			  
