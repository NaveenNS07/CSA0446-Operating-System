#include <stdio.h>

struct Process {
    int pid;      
    int burstTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
};

void sortByPriority(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].priority > proc[j + 1].priority) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time and priority for process %d: ", proc[i].pid);
        scanf("%d %d", &proc[i].burstTime, &proc[i].priority);
    }

    sortByPriority(proc, n);

    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    proc[0].waitingTime = 0; 

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            proc[i].waitingTime = proc[i - 1].waitingTime + proc[i - 1].burstTime;
        }
        proc[i].turnaroundTime = proc[i].waitingTime + proc[i].burstTime;

        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
    }
    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", 
               proc[i].pid, proc[i].burstTime, proc[i].priority, 
               proc[i].waitingTime, proc[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);

    return 0;
}
