#include <stdio.h>
#include <stdlib.h>   // For atoi() and exit()
#include <unistd.h>   // For fork(), getpid(), getppid()
#include <sys/types.h> // For pid_t
#include <sys/wait.h> // For wait()

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_children_in_chain>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    pid_t current_pid = getpid();
    int current_process_id = 0; // The count for the process in the chain

    for (int i = 0; i < n; i++) {
        pid_t child_pid = fork();

        if (child_pid < 0) {
            perror("fork failed");
            exit(1);
        }
        else if (child_pid == 0) {
            current_pid = getpid();
            current_process_id = i + 1; // Assign the next ID in the chain

        else {
            printf("Process %d → PID: %ld created Child %d (PID: %ld)\n", current_process_id, (long)current_pid, i + 1, (long)child_pid);

            waitpid(child_pid, NULL, 0);
            exit(0);
        }
    }

    // 3. Final Process in the Chain
    // This code is reached ONLY by the LAST process created (Process N).
    printf("Process %d → PID: %ld (The last link in the chain) is now exiting.\n",
           current_process_id, (long)current_pid);

    return 0;
}
