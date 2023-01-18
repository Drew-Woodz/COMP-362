//Andrew Lockwood
//10/24/22
//COMP362
//LAB9

#include "../inc/inverted.h"

// "hidden" symbols (i.e., not included in the .h file)

int tableSize;
int frameSize;

int lookUp(PROC *, int, int);
int findOldest(PROC *table);

/*
 * initializes the table for the given sizes of the memory and frame
 * all entries should be zeroed (e.g., calloc())
 */
void initInverted(PROC **table, int msize, int fsize)
{
    // DONE: implement
    //Initializes the table for the given sizes of the memory and frame. All entries should be zeroed (e.g., calloc())
    
    //Allocate table using calloc()
    *table = calloc(msize / fsize, sizeof(PROC *));
    //Initialize tableSize and framesize
    frameSize = fsize;
    tableSize = msize / fsize;


}


/*
 * translate a logical address <pid, page, offset> into a physical address
 * if there is no entry for the pid and the page number in the table, it has to be added
 * if there is no room in the table for the new entry, then the oldest entry has to be removed
 */
long translate(PROC *table, int pid, int page, int offset)
{
    // DONE: implement
    // Translate a logical address <pid, page, offset> into a physical address.
    long index = lookUp(table, pid, page);
    // if there is no entry for the pid and the page number in the table, it has to be added
    if (index == -1){
        // if there is no room in the table for the new entry, then the oldest entry has to be removed

        index = findOldest(table);
        table[index].pid = pid;
        table[index].page = page;
    }
    // Update Time
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    table[index].timeStamp = time.tv_sec * 1000000000 + time.tv_nsec;

    return index * frameSize + offset;



}

//
// find the entry for a given pid and page
//
int lookUp(PROC *table, int pid, int page)
{
    // DONE: implement
    // Find the entry for a given pid and page.
    for (int i = 0; i < tableSize; i++){
        if((table[i].pid == pid) && (table[i].page == page)){
            return i;

        }

    }
    return -1;


}

//
// find the oldest entry (or not used that has the timestamp == 0)
//
int findOldest(PROC *table)
{
    // DONE: implement
    // find the oldest entry (or not used that has the timestamp == 0).
    int oldest = 0;
    for (int i = 0; i < tableSize; i++){
        if(table[i].timeStamp > table[oldest].timeStamp){
            oldest = i;
        }

    }
    return oldest;

}


/***
 * prints the inverted table
*/
void printInverted(PROC *table)
{
    printf("-------------------------------------\n");
    printf("        INVERTED TABLE CONTENT\n");
    printf("-------------------------------------\n");
    printf("| PID | PAGE |       TIMESTAMP\n");
    printf("-------------------------------------\n");
    for (int i = 0; i < tableSize; i++)
        printf("| %3d | %4d | %20ld |\n", table[i].pid, table[i].page, table[i].timeStamp);
}
