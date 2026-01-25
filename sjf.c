#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Request {
    int rid;
    int arrival_time;
    int track_no;
    int head_movement;
    int completion_position;
    int total_movement;
    bool completed;
};

/* Display program title */
void displayHeader() {
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║        SJF DISK SCHEDULING SIMULATOR            ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
}

/* Display results */
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

    printf("\nTOTAL HEAD MOVEMENT\n");
    printf(" Total Seek Time : %d tracks\n", total_seek);
    printf(" Average Seek    : %.2f tracks\n", (float)total_seek / n);
}

int main() {
    int n, initial_head;

    displayHeader();

    printf("Enter number of disk requests (1–10): ");
    scanf("%d", &n);

    struct Request *requests = malloc(n * sizeof(struct Request));

    printf("Enter initial disk head position: ");
    scanf("%d", &initial_head);

    printf("\nENTER DISK REQUEST DETAILS\n");

    for (int i = 0; i < n; i++) {
        requests[i].rid = i + 1;
        requests[i].completed = false;

        printf("Request R%d:\n", requests[i].rid);

        printf("  Arrival Time : ");
        scanf("%d", &requests[i].arrival_time);

        printf("  Track Number : ");
        scanf("%d", &requests[i].track_no);
        printf("\n");
    }

    int current_head = initial_head;
    int total_movement = 0;
    int completed_count = 0;
    int time = 0;

    /*
     * SJF LOGIC:
     * At each time, select request with shortest seek distance
     */
    while (completed_count < n) {
        int idx = -1;
        int min_seek = 999999;

        for (int i = 0; i < n; i++) {
            if (!requests[i].completed && requests[i].arrival_time <= time) {
                int seek = abs(current_head - requests[i].track_no);

                if (seek < min_seek) {
                    min_seek = seek;
                    idx = i;
                }
            }
        }

        // If no request is ready, move time forward
        if (idx == -1) {
            time++;
            continue;
        }

        // Serve the shortest job
        requests[idx].head_movement = abs(current_head - requests[idx].track_no);
        total_movement += requests[idx].head_movement;

        requests[idx].total_movement = total_movement;
        requests[idx].completion_position = requests[idx].track_no;
        requests[idx].completed = true;

        current_head = requests[idx].track_no;
        completed_count++;

        // Assume disk service takes 1 unit time
        time++;
    }

    displayResults(requests, n);
    free(requests);
    return 0;
}
