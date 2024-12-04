#include <stdio.h>

struct Process {
    int pid;            
    int burstTime;      
    int remainingTime;  
    int waitingTime;    
    int turnaroundTime; 
};

void roundRobin(struct Process proc[], int n, int timeQuantum) {
    int currentTime = 0;
    int completed = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remainingTime > 0) {
                int executeTime = (proc[i].remainingTime > timeQuantum) ? timeQuantum : proc[i].remainingTime;
                currentTime += executeTime;
                proc[i].remainingTime -= executeTime;

                if (proc[i].remainingTime == 0) {
                    completed++;
                    proc[i].turnaroundTime = currentTime;
                    proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
                    totalWaitingTime += proc[i].waitingTime;
                    totalTurnaroundTime += proc[i].turnaroundTime;
                }
            }
        }
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    roundRobin(proc, n, timeQuantum);

    return 0;
}
