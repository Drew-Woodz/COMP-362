//Andrew Lockwood
//11/14/2022
//COMP 362
//Project 1
//Step 1

//////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2020 Prof. AJ Bieszczad. All rights reserved.
///
//////////////////////////////////////////////////////////////////////////

#include "disk.h"

disk_t disk;

/***
 *
 * Verifies correctness of the logical block address, and then translates it to a cylinder-head-sector equivalent.
 *
 */
CIDEV_RET_CODE lba2chs(lba_t lba, chs_t *chs)
{
    //Verifies correctness of the logical block address,
    if (lba >= MAX_LOGICAL_BLOCK)
        return CIDEV_ADDRESS_ERROR;

// TODO:DONE implement
    //and then translates it to a cylinder-head-sector equivalent.
        chs->cyl = lba /(NUM_OF_HEADS*NUM_OF_SECTS);
    //chs.head = (lba/NUM_OF_SECTS)/NUM_OF_HEADS;
    chs->head = (lba/NUM_OF_SECTS) % NUM_OF_HEADS;
    chs->sect = (lba % NUM_OF_SECTS);
    return CIDEV_SUCCESS;
}

/***
 *
 * Verifies correctness of the cylinder-head-sector address, and then translates it to a logical block address.
 *
 */
CIDEV_RET_CODE chs2lba(chs_t *chs, lba_t *lba)
{
// TODO:DONE implement
    //Verifies correctness of the cylinder-head-sector address
    if((chs->cyl * NUM_OF_SECTS * NUM_OF_HEADS) + (chs->sect) >= MAX_LOGICAL_BLOCK)
        return CIDEV_ADDRESS_ERROR;
    //and then translates it to a logical block address.
    //*lba = (chs.cyl*NUM_OF_SECTS * NUM_OF_HEADS)
    *lba = (chs->cyl* NUM_OF_SECTS * NUM_OF_HEADS) + chs->head * NUM_OF_SECTS + (chs->sect);

    return CIDEV_SUCCESS;

}


/***
 *
 * Verifies the parameters, then allocates space for the requested data (using
 * the caller-provided pointer buffer), copies the data from the disk to the buffer,
 * and appends '\0' to terminate the string.
 *
 */
CIDEV_RET_CODE readDisk(lba_t lba, unsigned int size, char **buffer)
{
// TODO:DONE verify parameters

    //Verifies the parameters

    if (size >= MAX_LOGICAL_BLOCK*SECT_SIZE){
        return CIDEV_SPACE_ERROR;
    }

    CIDEV_RET_CODE errCode = CIDEV_SUCCESS;

    unsigned int numSectors = 0, sizingVar = 0;
    
    /*if(size % SECT_SIZE == 0){
        numSectors = size;
        size = sizingVar;
    }*/
    if(size % SECT_SIZE == 0){
        numSectors = size / SECT_SIZE;
        sizingVar = size;
    }
    else{
        numSectors = (size / SECT_SIZE) + 1;
        sizingVar = size + ((SECT_SIZE) - (size % SECT_SIZE));
    }

    chs_t diskLocations[numSectors], chs;

    for (int i = 0; i < numSectors; ++i){
        if ((errCode = lba2chs((lba + i) % MAX_LOGICAL_BLOCK, &diskLocations[i])) != CIDEV_SUCCESS)
            return errCode;
    }

    // TODO:DONE implement
    // Then allocates space for the requested data (using * the caller-provided pointer buffer)
    *buffer = (char*)calloc(sizeof(char*), sizingVar + 1);
    printf("\nSize Variable in Read: %d\n", size);
    
    for (int i = 0; i < numSectors; i++){

        chs = diskLocations[i];

        if((size / SECT_SIZE) == 0){
            sizingVar = size;
        }
        else
            sizingVar = SECT_SIZE;


        strncat(*buffer, disk[chs.cyl][chs.head][chs.sect],sizingVar);

        size -= SECT_SIZE;
    }
    //and appends '\0' to terminate the string.
    strcat(*buffer,"\0");

    return errCode;
}

/***
 *
 * An auxiliary function to fill a single disk block with '.'
 *
*/
CIDEV_RET_CODE clearBlock(lba_t lba)
{
    char *writeBuffer;
#ifdef __DEBUG_DISK
    writeBuffer = malloc(SECT_SIZE);
#else
    writeBuffer = kmalloc(SECT_SIZE, GFP_USER);
#endif
    if (writeBuffer == NULL)
        return CIDEV_SPACE_ERROR;

    for (int i = 0; i < SECT_SIZE; i++)
        writeBuffer[i] = '.';

    CIDEV_RET_CODE errCode = writeDisk(lba, writeBuffer);

#ifdef __DEBUG_DISK
    free(writeBuffer);
#else
    kfree(writeBuffer);
#endif

    return errCode;
}

/***
 *
 * Validates the parameters, and then writes the caller-provided data to the disk starting at the block pointed
 * to by the logical block address.
 *
 */
CIDEV_RET_CODE writeDisk(lba_t lba, char *buffer)
{
// TODO:DONE verify the parameters


    CIDEV_RET_CODE errCode = CIDEV_SUCCESS;

 
   size_t  numSector, numChars = strlen(buffer);
   int remainingSize = numChars;

    //Validates the parameters
    if(numChars % SECT_SIZE == 0){
        numSector = numChars/SECT_SIZE;
    }
    else
        numSector = numChars/SECT_SIZE + 1;


    if(numSector >= MAX_LOGICAL_BLOCK){
        return CIDEV_SPACE_ERROR;
    }


    chs_t diskLocation[numSector], chs;


    for (int i = 0; i < numSector; ++i){
        if((errCode = lba2chs((lba + i) % MAX_LOGICAL_BLOCK, &diskLocation[i])) != CIDEV_SUCCESS){
            return errCode;
        }
    }
        // TODO: DONE implement
        /*and then writes the caller-provided data to the disk starting at the block pointed
        to by the logical block address.*/
    for (int i = 0; i < numSector; i++){
        chs = diskLocation[i];
        /*if ((numChars % SECT_SIZE) == 0){...no...}*/
        if ((numChars / SECT_SIZE) == 0){
            remainingSize = numChars;
        }

        else
            remainingSize = SECT_SIZE;


        strncpy(disk[chs.cyl][chs.head][chs.sect], buffer + i*SECT_SIZE, remainingSize);
        numChars -= SECT_SIZE;
        // remainingSize = numChars;
    }

    return errCode;
}
