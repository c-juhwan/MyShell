// Test program for Operating System lecture.
// This program tests a sytsem call function fork()

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)
        const char* os = "Windows";
#else
#ifdef __linux
        const char* os = "Linux";
#else
#ifdef __APPLE__
        const char* os = "Apple OS";
#else
        const char* os = "Unknown";
#endif
#endif
#endif

int main(void)
{
    // Defining constants for program
    const int sleeping_time = 1;
    const int parent_working_count = 5;
    const int child_working_count = 10;

    // Defining 
    pid_t pid = -1;
    char* message = NULL;
    int n = 0, i = 0;

    printf("<Testing fork() - Running system : %s>\n", os);
    printf("Parent will be excuted for : %d times\n", parent_working_count);
    printf("Child  will be excuted for : %d times\n", child_working_count);
    printf("\n");

    pid = fork();
    switch (pid)
    {
        case -1:
            perror("Fork failed. Exit.");
            exit(1);
        case 0:
            message = "Child  working";
            n = child_working_count;
            break;
        default:
            message = "Parent working";
            n = parent_working_count;
            break;    
    }

    for(; n > 0; n--)
    {
        printf("Execution %d, pid is : %d \t", i, pid);
        printf("%s\n", message);
        sleep(sleeping_time);
        i++;
    }

    // loop has ended and the process will be terminated
    // showing which process will be terminated
    if (pid == 0)
        printf("Execution X, pid is : %d \tChild  TERMINATED\n", pid);
    else // (pid != 0)
        printf("Execution X, pid is : %d \tParent TERMINATED\n", pid);

    return 0;
}