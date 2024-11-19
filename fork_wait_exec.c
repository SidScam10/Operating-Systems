#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    pid=fork();
    if(pid<0)
    {
        fprintf(stderr,"fork failed\n");
        return 1;
    }
    else if(pid==0)
    {
        printf("Child Process with PID %d",getpid());
        printf("Child Process' Parent PID: %d",getppid());

        /*exec() part
        char *args[]={"ls","-l",NULL};
        execvp("ls",args);
        
        perror("execvp failed");
        return 1;*/

        /*wait() part
        sleep(2);
        printf("Child Process Exiting");
        return 0;*/

        /*exit() part
        printf("Child Process is doing some work");
        sleep(2);
        printf("Child Process Exiting");
        
        printf("Child Process exiting with status 42\n");
        exit(42);*/
    }
    else
    {
        printf("Parent Process PID %d",getpid());
        printf("Parent Process has Child with PID %d",pid);

        pid_t child_pid;
        child_pid=wait(&status);

        if(child_pid==-1)
        {
            perror("wait failed");
            return 1;
        }

        if(WIFEXITED(status))
        {
            printf("Child Process with PID %d exited normally with exit status %d\n",child_pid,WEXITSTATUS(status));
        }
        else
        {
            printf("Child Process with PID %d exited abnormally",child_pid);
        }
    }
    return 0;
}