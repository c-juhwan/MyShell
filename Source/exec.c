// Test program for Operating System lecture.
// This program tests a sytsem call function exec()

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    char* const ps_argv[] = {"ps", "-ax", 0};
    char* const ps_envp[] = {"PATH=/bin:/usr/bin", "Term=console", 0};

    printf("<Testing exec() - Running system : %s>\n", os);

    //execlv("/bin/ps", ps_argv);
    //execlvp("ps", ps_argv);
    //execlve("/bin/ps", ps_argv, ps_envp);


    //execve("/bin/ps", ps_argv, ps_envp);
    //execlp("ls", "ls", "", 0); // Option exists
    //execlp("ls", "ls", 0);     // Option doesnt exist
    //system("ps -ax");


    char* _Input   = (char*)malloc(sizeof(char)*20);
    //char* _Option = (char*)malloc(sizeof(char)*10);

    scanf("%s", _Input);
    printf("%s", _Input);
    char* _Name = strtok(_Input, " ");
    char* _Option = strtok(_Input, " ");

    printf("%s %s", _Name, _Option);

    if(strcmp(_Option, "") == 0)
    {
        printf("Yes!");
    }
    else
    {
        printf("Bow wow");
    }

    return 0;
}

