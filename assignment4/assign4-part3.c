/* ========================================
 *   Program:   assign4-part3.c
 *   Class:     CS3733-001
 *   Due Date:  December 5th, 2019
 *   Author:    Anthony Castro
 * ========================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

/*
 *      Global Variables
 */
int nthreads;
int nextIndex = 1;
pthread_mutex_t chopsticks[5];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

/*
 *  Function:       pickUpChopsticks
 *  Parameter:      int indexT
 *  Description:    Determines mutex lock using Thread index
 */
void pickUpChopsticks(int indexT) {
    int left = (indexT + nthreads) % nthreads;
    int right = (indexT + 1) % nthreads;
    
    if (indexT & 1) {
        pthread_mutex_lock(&chopsticks[right]);
        pthread_mutex_lock(&chopsticks[left]);
        printf("Philosopher %d has picked up chopsticks \n", indexT);
    } else {
        pthread_mutex_lock(&chopsticks[left]);
        pthread_mutex_lock(&chopsticks[right]);
        printf("Philosopher %d has picked up chopsticks \n", indexT);
    }
    
}

/*
 *  Function:       putDownChopsticks
 *  Parameter:      int indexT
 *  Description:
 *                  Determines if Philosoper has 'finished' eatting,
 *                  unlocks given thread using index
 */
void putDownChopsticks(int indexT) {
    int chop = 0;
    printf("Philosopher %d has finished eating \n", indexT);
    pthread_mutex_unlock(&lock);
    
    int left = (indexT + nthreads) % nthreads;
    int right = (indexT + 1) % nthreads;
    chop = pthread_mutex_unlock(&chopsticks[right]);
    chop = pthread_mutex_unlock(&chopsticks[left]);
}

/*
 *  Function:       thinking
 *  Parameter:      int indexT
 *  Description:    Thread index used to sleep
 */
void thinking(int indexT) {
    int rand_num = rand() % 500 + 1;
    int sleep_time = rand_num % nthreads;
    
    printf("Philosopher %d thinks for %d seconds \n", indexT, sleep_time);
    sleep(sleep_time);
}

/*
 *  Function:       eating
 *  Parameter:      int indexT
 *  Description:    Determines if thread is "eatting" to sleep
 */
void eating(int indexT) {
    int rand_num = rand() % 500 + 1;
    int sleep_time = rand_num % nthreads;
    printf("Philosopher %d eats for %d seconds \n", indexT, sleep_time);
    sleep(sleep_time);
}

/*
 *  Method:         *func
 *  Parameter:      void *indexT
 */
void *func(void *indexT) {
    int threader = (int)indexT;
    thinking(threader);
    pthread_mutex_lock(&lock);
    while(nextIndex != ti) {
        pthread_cond_wait(&condition, &lock);
    }
    
    pickUpChopsticks(threader);
    eating(threader);
    putDownChopsticks(threader);
    
    nextIndex++;
    pthread_cond_broadcast(&condition);
    
    return NULL;
}

/*
 *  Main
 */
int main(int argc, char *argv[]) {
    nthreads = atoi(argv[1]);
    pthread_t tid[nthreads];
    srand(time(NULL));
    
    /*
     *      Check arguments from command line.
     */
    if(argc != 2) {
        printf("ERROR!\nUSAGE: 'assign4-part3.c' [Number of Threads to Create] \n");
        exit (1);
    }
    
    printf("Anthony Castro Assignment 4: # of threads = %d \n", nthreads);
    
    for (int i = 1; i <= nthreads; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }
    
    pthread_cond_init(&condition,NULL);
    pthread_mutex_init(&lock,NULL);
    
    for (int i = 1; i <= nthreads; i++) {
        pthread_create(&tid[i], NULL, (void *)func, (void *)i);
    }
    
    for (int i = 1; i <= nthreads; i++) {
        pthread_join(tid[i], NULL);
    }
    
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&condition);
    
    for (int i = 1; i <= nthreads; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }
    
    return 0;
}
