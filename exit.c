#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // fork() failed
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        
        // Simulate some work in the child process
        printf("Child process is doing some work...\n");
        sleep(2); // Simulate work with sleep

        // Exit with status 42
        printf("Child process exiting with status 42\n");
        exit(42);
    } else {
        // Parent process
        printf("Parent process: PID = %d\n", getpid());
        
        // Wait for the child process to terminate
        pid_t child_pid = wait(&status);

        if (child_pid == -1) {
            perror("wait failed");
            return 1;
        }

        // Check if the child process exited normally
        if (WIFEXITED(status)) {
            printf("Child process with PID %d exited with status %d\n", child_pid, WEXITSTATUS(status));
        } else {
            printf("Child process with PID %d did not exit normally\n", child_pid);
        }
    }

    return 0;
}
