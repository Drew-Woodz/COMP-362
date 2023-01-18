//Andreww Lockwood
//10/31/22
//COMP362
//LAB10
/**
 * This implements the LRU page-replacement algorithm.
 */

#include "../inc/lruList.h"

int *referenceStringLRU;
int refStringLengthLRU;

FRAME *pageTableTop;
FRAME *leastRecentlyUsed;
int pageTableSize;

int numberOfFramesPerProcess = 0;

// statistics
int nummberOfFaults = 0;

int hitPageNumberLRU;

/*
 * insert pages from a reference string into a page table and measure
 * the page fault rate
 */
int testLRU(int numOfFrames, int *refString, int refStrLen)
{
    // TODO: implement
    pageTableTop = NULL;

    numberOfFramesPerProcess = numOfFrames;

    for (int i = 0; i < numOfFrames; i++){
        FRAME *newFrame;
        newFrame = malloc(sizeof(FRAME));

        if (pageTableTop == NULL){
            newFrame->up = NULL;
            newFrame->pageNumber = -1;
            newFrame->down = NULL;
        }
        else{
            pageTableTop->down = newFrame;
            newFrame->up = pageTableTop;
            newFrame->pageNumber = -1;
            newFrame->down = NULL;
            nummberOfFaults++;
        }
        pageTableTop = newFrame;
    }
    while (pageTableTop->up != NULL){
        pageTableTop = pageTableTop->up;
    }

    leastRecentlyUsed = pageTableTop;

    for (int i = 0; i < refStrLen; i++){
        printf("%d ->\t", refString[i]);
        insertLRU(refString[i]);
    }

    return 0;

}

/*
 *	try to insert a page into the page table
 */
void insertLRU(int pageNumber)
{
    // TODO: implement
     hitPageNumberLRU = -1;

    FRAME *found = pageTableTop;

    if (pageTableSize == 0) {
        pageTableTop->pageNumber = pageNumber;
        leastRecentlyUsed = pageTableTop;
        pageTableSize++;
    } else {
        found = searchLRU(pageNumber);

        if (found == NULL) {
            pageTableSize++;
            nummberOfFaults++;
            if (pageTableSize > numberOfFramesPerProcess) {
                leastRecentlyUsed = leastRecentlyUsed->up;
            } else {
                found = pageTableTop;
                int prevPage = pageNumber;
                int currPage = found->pageNumber;

                found->pageNumber = pageNumber;

                for (int i = 0; i < pageTableSize; i++) {
                    found->pageNumber = prevPage;
                    found = found->down;
                    prevPage = currPage;
                    currPage = found->pageNumber; //blows up here
                }
            }
        } else {
            if (hitPageNumberLRU == 0) {}
            else if (hitPageNumberLRU == pageTableSize) {
                found->down->up = found->down;
                leastRecentlyUsed = found->up;
                found->up = NULL;
                found->down = pageTableTop;
                pageTableTop->up = found;
                pageTableTop = found;
            }
            else {
                found->up->down = found->down;
                found->down->up = found->up;
                pageTableTop->up = found;
                found->down = found;
                found->up = NULL;
                pageTableTop = found;
            }
        }
    }
    displayLRU();

}

/**
 * Searches for page pageNumber in the page frame list
 * returns NULL if a frame with pageNumber was not found
 * otherwise, returns a reference to the frame with pageNumber
 */
FRAME *searchLRU(int pageNumber)
{
    // TODO: implement
     FRAME *currFrame = pageTableTop;
    for(int i = 0; i < pageTableSize; i++){
        if(currFrame->pageNumber == pageNumber){
            hitPageNumberLRU = i;
            return currFrame;
        }
        currFrame = currFrame->down;
    }
    return NULL;
}

void displayLRU()
{
    // TODO: implement
    FRAME *currFrame = pageTableTop;

    if(hitPageNumberLRU != -1){
        for(int i = 0; i < pageTableSize; i++){
            if (i == 0){
                printf("%d<\t", currFrame->pageNumber);
            }
            else{
                printf("%d\t", currFrame->pageNumber);
            }
            currFrame = currFrame->down;
        }
        printf("\n");
        hitPageNumberLRU = -1;
    }
    else{
        for (int i = 0; i < pageTableSize; i++){
            printf("%d", currFrame->pageNumber);
            if ((i + 1) != pageTableSize){
                printf("\t");
            }
            currFrame = currFrame->down;
        }
        printf("*\n");
    }



}

void freePageTableLRU()
{
    // TODO: implement
        while (pageTableTop->down != NULL){//while this (pageTableTop) is not null
        pageTableTop = pageTableTop->down;//Go down the list 
        pageTableTop->up = NULL;//Delete one where you came from
        free(pageTableTop->up);//Free it too
    }
    free(pageTableTop);
    free(leastRecentlyUsed);//Free everything
}

