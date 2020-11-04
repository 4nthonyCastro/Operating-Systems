//
//  part3.c
//  cs3733-os-assign3
//
//  Created by Castro's on 3/23/19.
//
#include "part3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>

#include "phypages.h"
#include "pagetable.h"

int part3(int argc, char *argv[])
{
    /*
     * Page Table Information.
     */
    unsigned long offsetBit;
    unsigned long offset;
    unsigned long frame;
    unsigned long physicalAddress;
    unsigned long virtualAddress;
    
    int fileInput;
    int fileOutput;
    int error = 0;
    //int
    //int pageTable[32] = {2,4,1,7,3,5,6};
    
    /*
     * Check User Inputs.
     */
    if (argc != 5)
    {
        fprintf(stderr, "Invalid Parameters/File Name. %s\n", argv[0]);
        exit(2);
    }
    unsigned long pages = (unsigned long) atoi(argv[2]) / atoi(argv[1]);
    unsigned long frames = (unsigned long) atoi(argv[3]) / atoi(argv[1]);
    unsigned long pagesize = (unsigned long) ceil(log2(atoi(argv[1])));
    
    /*
     * Open input.output file.
     */
    fileInput = open(argv[1], O_RDONLY);
    fileOutput = open("output-part3", O_WRONLY|O_CREAT|O_TRUNC,0666);
    /*
     * Check input.output file.
     */
    if (fileInput == -1 || fileOutput == -1)
    {
        perror("Failed to open files.");
    }
    //Init the values from agrs
    offsetBit = pagesize;
    createPageTable(pages);
    createPhysicalSpace(frames);
    
    while(read(fileInput, &virtualAddress, sizeof(unsigned long)) == sizeof(unsigned long))
    {
        /*
         * Size of Virtual Page.
         */
        offset = virtualAddress & (atoi(argv[1]) - 1); //
        virtualAddress = virtualAddress >> offsetBit;
        error = convertPageToFrame(virtualAddress, &frame);
        
        if (error == -1) {
            fprintf(stderr, "[ERROR] in converting page to frame\n");
            exit(2);
        }
        /*
         * Left Shift to return physical base address.
         */
        physicalAddress = frame << offsetBit;
        physicalAddress = physicalAddress + offset;
        write(fileOutput, &physicalAddress, sizeof(unsigned long));
    }
    printf("Num of Page Faults: %d\n", getPageFaults());
    freePhysical();
    cleanUpVirtual();
    return 0;
}

