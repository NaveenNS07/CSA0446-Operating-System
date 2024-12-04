#include <stdio.h>

struct Process {
    int pid;             
    int burstTime;       
    int arrivalTime;     
    int waitingTime;     
    int turnaroundTime;  
    int completionTime;  
    int visited;         
};

int findShortestJob(struct Process proc[], int n, int currentTime) {
    int shortest = -1;
    int minBurst = 1e9; 

    for (int i = 0; i < n; i++) {
        if (!proc[i].visited && proc[i].arrivalTime <= currentTime && proc[i].burstTime < minBurst) {
            minBurst = proc[i].burstTime;
            shortest = i;
        }
    }
    return shortest;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", proc[i].pid);
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].visited = 0; // Mark process as not executed
    }

    int currentTime = 0, completed = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    while (completed < n) {
        // Find the next process to execute
        int shortest = findShortestJob(proc, n, currentTime);

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        currentTime += proc[shortest].burstTime;
        proc[shortest].completionTime = currentTime;
        proc[shortest].turnaroundTime = proc[shortest].completionTime - proc[shortest].arrivalTime;
        proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;
        proc[shortest].visited = 1; 
        completed++;

        totalWaitingTime += proc[shortest].waitingTime;
        totalTurnaroundTime += proc[shortest].turnaroundTime;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].waitingTime, proc[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / n);

    return 0;
}
