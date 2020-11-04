//
//  pagetable.c
//  cs3733-os-assign3
//
//  Created by Castro's on 3/20/19.
//
#include <stdio.h>
#include <stdlib.h>
#include "pagetable.h"
#include "phypages.h"

pageType *page = NULL;

int convertPageToFrame(unsigned long pageNum, unsigned long *frame)
{
    unsigned long tempFrame, pageSwapped; //If swap
    
    int error = 0;
    if (page[pageNum].valid == 0)
    { // If valid bit is zero then we need get swap from physical.
        error = getPhysicalSwap(pageNum, &pageSwapped, &tempFrame);
        if (error == -1)
        { // Make sure the getPhysicalSwap worked perfectly
            return -1;
        }
        page[pageSwapped].valid = 0;
        page[pageNum].frame = tempFrame;
        page[pageNum].valid = 1; //Reusing the frame so set valid bit to 1 again
        *frame = tempFrame;
        return 0;
    }else{                  // The page is valid and
        updateFrame(page[pageNum].frame);
        *frame = page[pageNum].frame;
        return 0;
    }
}
