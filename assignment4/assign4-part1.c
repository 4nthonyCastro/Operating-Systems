/* ========================================
*   Program:   assign4-part1.c
*   Class:     CS3733-001
*   Due Date:  December 5th, 2019
*   Author:    Anthony Castro
* ========================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
 *  Function:       phiosopherThread
 *  Parameter:      void *pVoid
 *  Description:    Index pointer utilzied to create thread
 */
void *philosopherThread(void *pVoid) {
    int theaderI = *(int *) pVoid;

    printf("This is philosopher %d\n", threaderI);
    pthread_exit(NULL);
}

/*
 *  Global Value nthreads
 */
int nthreads;

/*
 *  Function:       creatPhilosopher
 *  Parameter:      int nthreads
 *  Description:    nthreads is used for count of threads to be created
 */
void creatPhilosophers(int nthreads){
    printf("%d threads have been completed/joined successfully!\n", nthreads);
}

/*
 *  Main
 */
int main(int argc, char *argv[]) {
    int i;
    int nthreads = atoi(argv[1]);
    int tArr[nthreads];
    pthread_t tid[nthreads];
    
    /*
     *  Check Arguements from Command Line
     */
    if(argc != 2) {
        printf("Will only accept two parameters\n");
        exit (1);
    }
    
    /*
     *  Requirement (2): Print Name followed by Num of Threads
     */
    printf("Anthony Castro  Assignment 4: # of threads = %d \n", nthreads);
    
    /*
     *  Iterates through number of threads and creates threat with defined function
     */
    for(i = 0; i <= nthreads; i++){
        tArr[i] = i;
        /*
         *  Error check incase failed to create thread
         */
        if(pthread_create(&tid[i], NULL, philosopherThread, (void *) &tArr[i]) != 0) {
            printf("Failed to create thread at: %d\n", i);
            nthreads = i;
            break;
        }
    }
    
    /*
     *  Main thread iterating through all threads using pthread_join
     *  waiting for completion of all threads
     */
    for(i = 0; i <= nthreads; ++i) {
        pthread_join(tid[i], NULL);
    }
    
    /*
     *  Requirement (5) calls creatPhilosopher functions informing user of thread completion
     */
    creatPhilosophers(nthreads);
    return(0);
}
