#include <stdio.h>
#include <stdlib.h>

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
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void displayHeader() {
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║       FCFS CPU Scheduling Simulator            ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
}

void displayResults(struct Process p[], int n) {
    int total_wt = 0, total_tat = 0;
    
    printf("\n╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                    SCHEDULING RESULTS                     ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n\n");
    
    printf("┌─────┬─────┬─────┬─────┬─────┬─────┐\n");
    printf("│ PID │ AT  │ BT  │ CT  │ TAT │ WT  │\n");
    printf("├─────┼─────┼─────┼─────┼─────┼─────┤\n");
    
    for (int i = 0; i < n; i++) {
        printf("│ P%-2d │ %-3d │ %-3d │ %-3d │ %-3d │ %-3d │\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].completion_time,
               p[i].turnaround_time,
               p[i].waiting_time);
        
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
    }
    
    printf("└─────┴─────┴─────┴─────┴─────┴─────┘\n");
    
    printf("\n┌─────────────────────────────────────────┐\n");
    printf("│ AT  = Arrival Time                      │\n");
    printf("│ BT  = Burst Time                        │\n");
    printf("│ CT  = Completion Time                   │\n");
    printf("│ TAT = Turnaround Time (CT - AT)         │\n");
    printf("│ WT  = Waiting Time (TAT - BT)           │\n");
    printf("└─────────────────────────────────────────┘\n");
    
    printf("\n╔═══════════════════════════════════════════════╗\n");
    printf("║           AVERAGE PERFORMANCE                 ║\n");
    printf("╠═══════════════════════════════════════════════╣\n");
    printf("║ Average Waiting Time      : %.2f              ║\n", (float)total_wt / n);
    printf("║ Average Turnaround Time   : %.2f              ║\n", (float)total_tat / n);
    printf("╚═══════════════════════════════════════════════╝\n\n");
}

void displayGanttChart(struct Process p[], int n) {
    printf("\n╔═══════════════════════════════════════════════╗\n");
    printf("║              GANTT CHART                      ║\n");
    printf("╚═══════════════════════════════════════════════╝\n\n");
    
    // Top border
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("─────────");
    }
    printf("\n│");
    
    // Process names
    for (int i = 0; i < n; i++) {
        printf("   P%-2d  │", p[i].pid);
    }
    printf("\n ");
    
    // Bottom border
    for (int i = 0; i < n; i++) {
        printf("─────────");
    }
    printf("\n");
    
    // Timeline
    int start_time = p[0].arrival_time;
    printf("%-2d", start_time);
    for (int i = 0; i < n; i++) {
        printf("       %-2d", p[i].completion_time);
    }
    printf("\n\n");
}

int main(void) {
    int n;
    
    displayHeader();
    
    // Get number of processes
    printf("Enter the number of processes (1-10): ");
    while (scanf("%d", &n) != 1 || n < 1 || n > 10) {
        printf("Invalid input! Please enter a number between 1 and 10: ");
        while (getchar() != '\n'); // Clear input buffer
    }
    
    struct Process *p = (struct Process *)malloc(n * sizeof(struct Process));
    if (p == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    int current_time = 0;
    
    // INPUT
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("         ENTER PROCESS DETAILS\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process P%d:\n", p[i].pid);
        
        printf("  Arrival Time: ");
        while (scanf("%d", &p[i].arrival_time) != 1 || p[i].arrival_time < 0) {
            printf("  Invalid! Enter a non-negative value: ");
            while (getchar() != '\n');
        }
        
        printf("  Burst Time  : ");
        while (scanf("%d", &p[i].burst_time) != 1 || p[i].burst_time <= 0) {
            printf("  Invalid! Enter a positive value: ");
            while (getchar() != '\n');
        }
        
        printf("\n");
    }
    
    // SORT BY ARRIVAL TIME
    sortByArrival(p, n);
    
    // FCFS SCHEDULING
    for (int i = 0; i < n; i++) {
        // If CPU is idle, jump to next process arrival
        if (current_time < p[i].arrival_time) {
            current_time = p[i].arrival_time;
        }
        
        p[i].completion_time = current_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        
        current_time = p[i].completion_time;
    }
    
    // OUTPUT
    displayGanttChart(p, n);
    displayResults(p, n);
    
    free(p);
    return 0;
}