//Andreww Lockwood
//10/31/22
//COMP362
//LAB10
/*
 * This implements the OPT page-replacement algorithm.
*/
#include "../inc/optArray.h"

int *referenceString;
int refStringLength;

// the page frame list
int *pageTable;
int numOfFramesPerProcess;

int victimIndex;
int hitPageNumber;

// statistics
int numOfFaults;

// this index is used to go through the sequence of pages references
int currentPgeReferenceIndex;

int testOPT(int numOfFrames, int *refString, int refStrLen)
{
    // TODO:DONE implement
    refStringLength = refStrLen;
    referenceString = refString;
    numOfFramesPerProcess = numOfFrames;
    pageTable = calloc(numOfFrames, sizeof(int));

    hitPageNumber = FREE_SLOT;
    victimIndex = FREE_SLOT;
    for(int frame = 0; frame < numOfFrames; ++frame){//Prepare pageTable
        pageTable[frame] = FREE_SLOT;
    }

    currentPgeReferenceIndex = 0;

    while(currentPgeReferenceIndex < refStringLength){//while current page has not reached the refStringLength
        insertOPT(referenceString[currentPgeReferenceIndex]);
        displayOPT();
        currentPgeReferenceIndex++;
    }

    //Free tables
    freePageTableOPT();
    return numOfFaults;
}

/*
 *	try to insert a page into the page table
 */
void insertOPT(int pageNumber){

    int searchVal = searchOPT(pageNumber);
    pageTable[searchVal] = pageNumber;
}

/*
 *  find either an empty slot, or the page, or a vitim to evict
 */
int searchOPT(int pageNumber)
{
    // TODO:DONE implement
    //For the whole pageTable Array
    for(int frame = 0; frame < numOfFramesPerProcess; ++frame){
        
        if(FREE_SLOT == pageTable[frame]){//Empty frame with found pageNumber 
            victimIndex = frame;
            numOfFaults++;
            return victimIndex;
        }
        if(pageNumber == pageTable[frame]){//Frame found
            hitPageNumber = frame;
            return hitPageNumber;
        }
    }
    numOfFaults++;

    return findVictimPageOPT();
}




int findVictimPageOPT()
{
    // TODO:DONE implement
    //Find and replace the page that is not be used for the longest time
    int longestTimeUnused = 0;
    int found;

    for(int frame = 0; frame < numOfFramesPerProcess; ++frame){
        found = -1;
        //Iterate Through refence string for longest unused period of time of a page
        for (int refStrIndex = currentPgeReferenceIndex; refStrIndex < refStringLength; ++refStrIndex){
            if (pageTable[frame] == referenceString[refStrIndex]){// Found frame pageNumber in Ref string again
                found = 1;
                //Look for unsued victimIndex or a longer unused time
                if(FREE_SLOT == victimIndex || longestTimeUnused < refStrIndex - currentPgeReferenceIndex){
                    victimIndex = frame;
                    longestTimeUnused = refStrIndex - currentPgeReferenceIndex;
                }
                break;
            }
        }
        if(-1 == found){
            return frame;
        }
    }
    return victimIndex;
}

void displayOPT()
{
    // TODO:DONE implement
    printf("%d ->", referenceString[currentPgeReferenceIndex]);
    for (int frame = 0; frame < numOfFramesPerProcess; ++frame){
        printf("\t");
        printf("%d", pageTable[frame]);
        if (hitPageNumber == frame){
            printf("<");
        }
        else if(victimIndex == frame){
        printf("*");
        victimIndex = FREE_SLOT;
        }
    }
    printf("\n");


}

void freePageTableOPT()
{
    // TODO:DONE implement
    free(pageTable);//Free table
}
