//Aaron Gould
//CGS3769
//Professor Markle
//03/14/2024


//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>


//macros
#define EXIT 0
#define INVALID -1
#define CPU 1
#define PID 5
#define RACE 2
#define BANKER 3
#define PROCESS 5
#define RESOURCE 3
#define TRUE 1
#define FALSE 0
#define MEMORY 4
#define FIRST 0
#define BEST 1
#define WORST 2
#define NEXT 3

// Function prototypes
int displayMenu();
void cpuScheduling();
void fcfs(int process[], int at[], int bt[], int i);
void sjf(int process[], int at[], int bt[], int i);
void displaySchedule(int process[], int at[], int bt[], int wt[], int tat[], int i);
void raceCondition();
void* threadFuncOne(void* arg);
void* threadFuncTwo(void* arg);
void bankersAlgorithm(); //new 
void systemState(int feasible[], int safe[]);
void memoryManagement();
void nextFit(int blockSize[], int blocks, int processSize[], int processes);
void firstFit(int blockSize[], int blocks, int processSize[], int processes);
void bestFit(int blockSize[], int blocks, int processSize[], int processes);
void worstFit(int blockSize[], int blocks, int processSize[], int processes);
void displayProcess(int allocation[], int processes, int processSize[]);

//Global Variable
int resource = 5;

//main function
int main() {
    int choice = INVALID;

    while (choice != EXIT) {
        choice = displayMenu();
        //Switches between which function in the menu. Added race condition function if selected
        switch (choice) {
            case CPU:
                cpuScheduling(); //trigger the first option
                break;
            case RACE:
                raceCondition();
                break;
            case BANKER:
                bankersAlgorithm();
                break;
            case MEMORY:
                memoryManagement();
                break;
            case EXIT:
                exit(EXIT);
        }
    }
    return 0;
}

//menu display function with print statements and taking user input 
int displayMenu() {
    int choice = INVALID;

    while (choice == INVALID) {
        printf("\n\t\t\t\t\t********** Operating System Management Menu ********** \n");
        printf("Select the OS program to run, enter the number of your selection. \n");
        printf("1. CPU Scheduling\n");
        printf("2. Race Condition\n");
        printf("3. Banker's Algorithm\n"); 
        printf("4. Memory Management\n"); //new print line
        printf("0. Exit\n");
        scanf("%d", &choice);
        //updated logic to MEMORY, will update when we add more options
        if (choice < EXIT && choice > MEMORY) {
            choice = INVALID;
        }
    }

    return choice;
}

//function cpuscheduling
//Setting up the arrays for process arrvtime and bursttime
void cpuScheduling() {
    int process[] = {1, 2, 3, 4, 5};
    int at[] = {0, 2, 4, 6, 7};
    int bt[] = {8, 5, 10, 2, 3};
    
    printf("\n*************FCFS*************\n");
    fcfs(process, at, bt, PID);
    
    printf("\n*************SJF*************\n");
    sjf(process, at, bt, PID);
   
}

// function for first come first serve
void fcfs(int process[], int at[], int bt[], int i) {
    //declaring variables
    int wt[PID]; 
    int tat[PID];

    wt[0] = 0; //intializing index 0

    for (int i = 1; i < PID; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }

    for (int i = 0; i < PID; i++) {
        tat[i] = bt[i] + wt[i];
    }
    //displays the results in terminal
    displaySchedule(process, at, bt, wt, tat, i);
}

// function for short job first
void sjf(int process[], int at[], int bt[], int i) {
    //declaring variables
    int wt[PID];
    int tat[PID];
    int idx;
    int temp;

    for (int i = 0; i < PID; i++) {
        idx = i;
        for (int j = i + 1; j < PID; j++) {
            if (bt[j] < bt[idx]) {
                idx = j;
            }
        }
        //temporarily storing burst time
        temp = bt[i];
        bt[i] = bt[idx];
        bt[idx] = temp;

        temp = process[i];
        process[i] = process[idx];
        process[idx] = temp;

        temp = at[i];
        at[i] = at[idx];
        at[idx] = temp;
    }

    wt[0] = 0;

    for (int i = 1; i < PID; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }

    for (int i = 0; i < PID; i++) {
        tat[i] = bt[i] + wt[i];
    }
    //displays the results in terminal
    displaySchedule(process, at, bt, wt, tat, i);
}
//function forstructing of the schedule with print statements and the calcs for averages
void displaySchedule(int process[], int at[], int bt[], int wt[], int tat[], int i) {
    int totWt = 0;
    int totTat = 0;
    float avgWt = 0;
    float avgTat = 0;
    
    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    printf("\n---\t---\t---\t---\t---\t\n");
    for (int i = 0; i < PID; i++) {
        totWt += wt[i];
        totTat += tat[i];
        printf("%d\t%d\t%d\t%d\t%d\n", process[i], at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n");
    
    avgWt = (float)totWt / PID;
    avgTat = (float)totTat / PID;
    printf("Average Wait Time = %.2f\n", avgWt);
    printf("Average Turnaround Time = %.2f\n", avgTat);
}
//race condition function 
void raceCondition(){
    pthread_t threadOne, threadTwo;

    //First and second thread creation
    pthread_create(&threadOne, NULL, threadFuncOne, NULL);
    pthread_create(&threadTwo, NULL, threadFuncTwo, NULL);
    //join first and second threads
    pthread_join(threadOne, NULL);
    pthread_join(threadTwo, NULL);
    //last statement in output, outputs option 1 in the testcase
    printf("Value of shared resource is %d\n", resource);
}
//thread function one 
void* threadFuncOne(void* arg){
    //declaring variables
    int threadId = 1;
    int fOne = resource;
   
    //thread one statements and increments to add, and storing values
    printf("Thread 1 reads the value of shared resource as %d\n", fOne);
    fOne++;
    printf("Local update by Thread 1: %d\n", fOne);
    sleep(1);
    resource = fOne;
    printf("Value of shared resource updated by Thread 1 is: %d\n", resource);
}
//thread function two
void* threadFuncTwo(void* arg){
    //declaring variables
    int threadId = 2;
    int fTwo = resource;

    //thread two statements and decrements to subtract
    printf("Thread 2 reads the value of shared resource as %d\n", fTwo);
    fTwo--;
    printf("Local update by Thread 2: %d\n", fTwo);
    sleep(1);
    resource = fTwo;
    printf("Value of shared resource updated by Thread 2 is: %d\n", resource);
}

void bankersAlgorithm(){
    //2d array with 5rows 3 cols for allocation
    int allocation[PROCESS][RESOURCE] = {
        { 0, 0, 2 },
        { 3, 0, 2 },
        { 0, 1, 0 },
        { 2, 1, 1 },
        { 2, 0, 0 }
    };
    //2d array with 5 rows 3 cols for maxDemand
    int maxDemand[PROCESS][RESOURCE] = {
        { 4, 3, 3 },
        { 9, 0, 2 },
        { 7, 5, 3 },
        { 2, 2, 2 },
        { 3, 2, 2 }
    };
    //2d arrays for calculations for needs, available resources, storing feasible resource allocations, and storing safe resource allocation
    int available[RESOURCE] = { 2, 4, 6 };
    int need[PROCESS][RESOURCE];
    int feasible[PROCESS] = {0};
    int safe[PROCESS];
    int safeIdx = 0;

    // Calc needed for resources, iterating through
    for (int p = 0; p < PROCESS; p++){
        for (int r = 0; r < RESOURCE; r++){
            need[p][r] = maxDemand[p][r] - allocation[p][r];
        }
    }
    //bankers algorithm process
    for (int i = 0; i < PROCESS; i++){
        for (int p = 0; p < PROCESS; p++){
            if (feasible[p] == FALSE){
                int isUnsafe = FALSE;
                for (int r = 0; r < RESOURCE; r++){
                    if (need[p][r] > available[r]){
                        isUnsafe = TRUE;
                        break;
                    }
                }
                if (isUnsafe == FALSE){
                    safe[safeIdx++] = p;
                    for (int r = 0; r < RESOURCE; r++){
                        available[r] += allocation[p][r];
                    }
                    feasible[p] = TRUE;
                }
            }
        }
    }
    systemState(feasible, safe);
}



//function systemstate, checks the state of the system, wont print if working correctly
void systemState(int feasible[], int safe[]){
    int isSafe = TRUE;
    for (int p = 0; p < PROCESS; p++){
        if (feasible[p] == FALSE){
            isSafe = FALSE;
            printf("The system is not safe.\n");
            break;
        }
    }
    //output of bankers algo function
    if (isSafe == TRUE){
        printf("Safe resource allocation to process sequence\n");
        for (int p = 0; p < PROCESS; p++){
            printf(" P%d ->", safe[p]);
        }
        printf("\n");
    }
}
//memory management function
void memoryManagement(){
    
    printf("********** Memory Management **********\n\n");
    //when cycling through the algorithm and picks a case
    for (int algorithm = FIRST; algorithm <= NEXT; algorithm++) {
        int blockSize[] = {70, 20, 45, 65, 40, 80};
        int processSize[] = {15, 35, 25, 45, 60, 20};
        int blocks = sizeof(blockSize) / sizeof(blockSize[0]);
        int processes = sizeof(processSize) / sizeof(processSize[0]);
        switch (algorithm) {
            case FIRST:
                printf("\n********** First Fit **********\n\n");
                firstFit(blockSize, blocks, processSize, processes);
                break;
            case BEST:
                printf("\n********** Best Fit **********\n\n");
                bestFit(blockSize, blocks, processSize, processes);
                break;
            case WORST:
                printf("\n********** Worst Fit **********\n\n");
                worstFit(blockSize, blocks, processSize, processes);
                break;
            case NEXT:
                printf("\n********** Next Fit **********\n\n");
                nextFit(blockSize, blocks, processSize, processes);
                break;
        }
    }
}
//function next fit 
void nextFit(int blockSize[], int blocks, int processSize[], int processes){
    int allocation[processes];
    int id = 0;
    //function memset
    memset(allocation, INVALID, sizeof(allocation));
    //loop construct thru number of processes
    for (int i = 0; i < processes; i++){
        while (id < blocks){
            if (blockSize[id] >= processSize[i]){
                allocation[i] = id;
                blockSize[id] -= processSize[i];
                break;
            }
            id = (id + 1) % blocks;
        }
    }
    displayProcess(allocation, processes, processSize);
}
//functoin firstfit
void firstFit(int blockSize[], int blocks, int processSize[], int processes){
    int allocation[processes];

    memset(allocation, INVALID, sizeof(allocation));

    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    displayProcess(allocation, processes, processSize); // Display process allocation
}
//BEST FIT is causing issues with process no 6 block no should be 4 not 3.
void bestFit(int blockSize[], int blocks, int processSize[], int processes){
    int allocation[processes];

    memset(allocation, INVALID, sizeof(allocation));

    for (int i = 0; i < processes; i++) {
        int bestIdx = INVALID;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == INVALID || blockSize[j] <= blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != INVALID) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    displayProcess(allocation, processes, processSize);
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes){
    int allocation[processes];

    memset(allocation, INVALID, sizeof(allocation));

    for (int i = 0; i < processes; i++) {
        int wstIdx = INVALID;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (wstIdx == INVALID || blockSize[j] > blockSize[wstIdx]) {
                    wstIdx = j;
                }
            }
        }
        if (wstIdx != INVALID) {
            allocation[i] = wstIdx;
            blockSize[wstIdx] -= processSize[i];
        }
    }

    displayProcess(allocation, processes, processSize);
}

void displayProcess(int allocation[], int processes, int processSize[]){
    printf("Process No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] == INVALID) {
            printf("Not Allocated\n");
        } 
        else {
            printf("%d\t\n", allocation[i]+1);
        }
    }
    
}