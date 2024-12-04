#include <stdio.h>

#define MAX 100

struct Process {
    int pid;           
    int burstTime;    
    int arrivalTime;   
    int priority;      
    int remainingTime; 
    int waitingTime;   
    int turnaroundTime;
    int completed;     
};

void calculateTimes(struct Process proc[], int n) {
    int completed = 0, currentTime = 0, shortest = -1;
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    while (completed < n) {
        int minPriority = MAX;
        shortest = -1;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && !proc[i].completed && proc[i].priority < minPriority) {
                minPriority = proc[i].priority;
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        proc[shortest].remainingTime--;

        if (proc[shortest].remainingTime == 0) {
            proc[shortest].completed = 1;
            completed++;
            proc[shortest].turnaroundTime = currentTime + 1 - proc[shortest].arrivalTime;
            proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;

            totalWaitingTime += proc[shortest].waitingTime;
            totalTurnaroundTime += proc[shortest].turnaroundTime;
        }

        currentTime++;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               proc[i].pid, proc[i].arrivalTime, proc[i].burstTime, 
               proc[i].priority, proc[i].waitingTime, proc[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", proc[i].pid);
        scanf("%d %d %d", &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].completed = 0;
    }

    calculateTimes(proc, n);

    return 0;
}
