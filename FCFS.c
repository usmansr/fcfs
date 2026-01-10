#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

void sortByArrival(struct Process p[], int n) {
    struct Process temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].arrival_time > p[j + 1].arrival_time) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int main(void)
{
    int n = 5;
    struct Process p[n];
    int current_time = 0;

    // INPUT
    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].arrival_time);
        printf("Enter Burst Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].burst_time);
    }

    // SORT BY ARRIVAL TIME
    sortByArrival(p, n);

    // FCFS SCHEDULING
    for(int i = 0; i < n; i++) {
        if(current_time < p[i].arrival_time) {
            current_time = p[i].arrival_time;
        }

        p[i].completion_time = current_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

        current_time = p[i].completion_time;
    }

    // OUTPUT
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].completion_time,
               p[i].turnaround_time,
               p[i].waiting_time);
    }

    return 0;
}
