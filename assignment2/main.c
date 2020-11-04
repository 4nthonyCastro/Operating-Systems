//
//  main.c
//  assign2_cs3733
//
//  Created by Castro's on 2/24/19.
//  Copyright © 2019 Castro's. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define FIFO 1
#define SJF  2
#define PR   3
#define RR   4

/*
** Structure for PCB
*/
typedef struct PCB_st {
    int ProcId;
    int ProcPR;
    int CPUBurst;
    int Reg[8];
    int queueEnterClock, waitingTime;
    struct PCB_st *next;
} PCB_st;

/*
** Declare Mathods
** Initiate Global Variables.
*/
int fileRead(char *argv[ ], int flag);
int FIFO_Scheduling(PCB_st *PCB);
int total_waiting_time = 0, total_turnaround_time = 0, total_job = 0;
int CLOCK = 0;
int CPUReg[8] = {0};

int main(int argc, char *argv[ ]) {
    char *alg = argv[2];
    int flag;
    
    if (strcmp(argv[2], "FIFO") == 0) {
        if (argc != 5) {
            fprintf(stderr, "USAGE: prog -alg FIFO -input fileName\n");
            return -1;
        }
        
        flag = FIFO;
        fileRead(argv, flag);
    }
    
    fflush(stderr);
    return 0;
}

/*
** File Read.
*/
int fileRead(char *argv[ ], int flag) {
    FILE *inputFile;
    struct PCB_st *head = NULL;
    struct PCB_st *tail = NULL;
    char buffer[100];
    int scan;
    
    /*
    ** Malloc for Linked List.
    */
    head = (struct PCB_st*)malloc(sizeof(PCB_st));
    tail = (struct PCB_st*)malloc(sizeof(PCB_st));
    
    /*
    ** fopen file for reading.
    */
    inputFile = fopen(argv[4], "r");
    
    /*
    ** Read line by line into PCB
    */
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        struct PCB_st *pcb;
        int i;
        int ProcId, ProcPR, CPUBurst;
        
        scan = sscanf(buffer, "%d %d %d", &ProcId, &ProcPR, &CPUBurst);
        if (scan != 3) {
            fprintf(stderr, "Line does not contain 2 digits\n");
            continue;
        }
        
        /*
        ** Allocate Memory.
        */
        pcb = malloc(sizeof(PCB_st));
        pcb->ProcId = ProcId;
        pcb->ProcPR = ProcPR;
        pcb->CPUBurst = CPUBurst;
        for (i = 0; i <= 8; i++) {
            pcb->Reg[i] = pcb->ProcId;
        }
        pcb->queueEnterClock = 0;
        pcb->waitingTime = 0;
        pcb->next = NULL;
        
        /*
        ** Append Struct with Linked List.
        */
        if (head == NULL) {
            head = pcb;
        } else {
            while (tail->next != NULL) {
                tail = tail->next;
            }
            
            tail->next = pcb;
        }
    }
    
    /*
    ** Close File
    ** Print Student Name, Input File, CPU Scheduling Alg.
    */
    fclose(inputFile);
    printf("Student Name : Anthony Castro \n");
    printf("Input File Name : %s \n", argv[4]);
    printf("CPU Scheduling Alg : %s \n", argv[2]);
    
    switch (flag) {
        case FIFO:
            /*
            ** FIFO Head
            */
            while (head != NULL) {
                printf("A\n");
                head = head->next;
            }
            break;
    }
    
    return 0;
}

/*
** FIFO
*/
int FIFO_Scheduling(PCB_st *PCB) {
    struct PCB_st *temp = NULL;
    int PCB_num = 1;
    int i;
    
    /*
    ** Run through list.
    */
    while (PCB != NULL) {
        
        /*
        ** Context Switching
        */
        for (i = 0; i < 8; i++) {
            CPUReg[i] = PCB->Reg[i];
            CPUReg[i]++;
            PCB->Reg[i] = CPUReg[i];
        }
        
        /*
        ** Performance Metrics.
        */
        PCB->waitingTime = PCB->waitingTime + CLOCK - PCB->queueEnterClock;
        total_waiting_time = total_waiting_time + PCB->waitingTime;
        CLOCK = CLOCK + PCB->CPUBurst;
        total_turnaround_time = total_turnaround_time + CLOCK;
        total_job = total_job + 1;
        
        printf("Process %d is completed at %d ms\n", PCB_num, CLOCK);
        
        // Continue to next node
        PCB_num++;
        temp = PCB;
        free(PCB);
        PCB = temp;
    }
    
    printf("Average Waiting Time: %d\n", total_waiting_time/total_job);
    printf("Average Turnaround Time: %d\n", total_turnaround_time/total_job);
    printf("Throughput: %d\n", total_job/CLOCK);
    return 0;
}
