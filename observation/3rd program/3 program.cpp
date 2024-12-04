#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int pid;             
    int burst_time;       
    int waiting_time;     
    int turnaround_time;  
    int completion_time;  
};

void findWaitingTime(struct Process processes[], int n) {
    processes[0].waiting_time = 0; 
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
}

void findTurnaroundAndCompletionTime(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        processes[i].completion_time = processes[i].turnaround_time; 
    }
}

void printTable(struct Process processes[], int n) {
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].pid, 
               processes[i].burst_time, 
               processes[i].waiting_time, 
               processes[i].turnaround_time, 
               processes[i].completion_time);
    }
}

int main() {
    int n;

    printf("Enter the number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);

    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes. Please enter a number between 1 and %d.\n", MAX_PROCESSES);
        return 1;
    }

    struct Process processes[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1; 
        printf("Enter burst time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);

        if (processes[i].burst_time <= 0) {
            printf("Invalid burst time. Please enter a positive integer.\n");
            return 1;
        }
    }

    findWaitingTime(processes, n);
    findTurnaroundAndCompletionTime(processes, n);

    printTable(processes, n);

    return 0;
}

