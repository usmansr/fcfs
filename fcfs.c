#include <stdio.h>
#include <stdlib.h>

/*
 * Structure to represent a single disk request
 */
struct Request {
    int rid;                    // Request ID
    int arrival_time;           // Time at which request arrives
    int track_no;               // Requested track number
    int head_movement;          // Movement needed to serve this request
    int completion_position;    // Head position after servicing request
    int total_movement;         // Cumulative head movement till this request
};

/*
 * Sort requests based on arrival time (FCFS order)
 * Simple bubble sort since input size is small
 */
void sortByArrival(struct Request r[], int n) {
    struct Request temp;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (r[j].arrival_time > r[j + 1].arrival_time) {
                temp = r[j];
                r[j] = r[j + 1];
                r[j + 1] = temp;
            }
        }
    }
}

/*
 * Display program title
 */
void displayHeader() {
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║       FCFS DISK SCHEDULING SIMULATOR           ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
}

/*
 * Display final scheduling results and statistics
 */
void displayResults(struct Request r[], int n) {
    int total_seek = 0;

    printf("│ RID │ AT  │ TRACK  │ SEEK   │ HEAD POS │\n");

    for (int i = 0; i < n; i++) {
        printf("│ R%-2d │ %-3d │ %-6d │ %-6d │ %-8d │\n",
               r[i].rid,
               r[i].arrival_time,
               r[i].track_no,
               r[i].head_movement,
               r[i].completion_position);

        total_seek += r[i].head_movement;
    }

    printf("\n          TOTAL HEAD MOVEMENT\n");
    printf(" Total Seek Time : %d tracks\n", total_seek);
    printf(" Average Seek    : %.2f tracks\n", (float)total_seek / n);
}

int main(void) {
    int n, initial_head;

    displayHeader();

    printf("Enter number of disk requests (1–10): ");
    scanf("%d", &n);

    // Dynamically allocate memory for requests
    struct Request *requests = malloc(n * sizeof(struct Request));

    printf("\nEnter initial disk head position: ");
    scanf("%d", &initial_head);

    printf("\n         ENTER DISK REQUEST DETAILS\n");

    // Input request details
    for (int i = 0; i < n; i++) {
        requests[i].rid = i + 1;

        printf("Request R%d:\n", requests[i].rid);

        printf("  Arrival Time : ");
        scanf("%d", &requests[i].arrival_time);

        printf("  Track Number : ");
        scanf("%d", &requests[i].track_no);

        printf("\n");
    }

    // FCFS requires sorting by arrival time
    sortByArrival(requests, n);

    int current_head = initial_head;
    int total_movement = 0;

    /*
     * FCFS Disk Scheduling Logic
     * Serve requests strictly in arrival order
     */
    for (int i = 0; i < n; i++) {
        requests[i].head_movement = abs(current_head - requests[i].track_no);
        total_movement += requests[i].head_movement;

        requests[i].total_movement = total_movement;
        requests[i].completion_position = requests[i].track_no;

        // Move disk head to current track
        current_head = requests[i].track_no;
    }

    displayResults(requests, n);

    free(requests);
    return 0;
}
