#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // fork() failed
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("This is the child process. PID: %d\n", getpid());
        printf("Child's parent PID: %d\n", getppid());
    } else {
        // Parent process
        printf("This is the parent process. PID: %d\n", getpid());
        printf("Parent created a child process with PID: %d\n", pid);
    }

    return 0;
}
