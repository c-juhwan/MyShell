/**
 * @mainpage
 * @brief This is a my shell project.
 * @details It tries to work like a bash shell.
 * 
 * @version 1.0
 * @date 2020-09-12
 * 
 * @todo The command "cd" seems not to work.
 */

/**
 * @file shell.c
 * @author Juhwan Choi (gold5230@cau.ac.kr)
 * @brief Main file of this project
 * 
 * @version 1.0
 * @date 2020-09-11
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @var OSNAME
 * @brief Finds and define os name
 */
#if defined(_WIN32) || defined(_WIN64)
        const char* OSNAME = "Windows";
#else
#ifdef __linux
        const char* OSNAME = "Linux";
#else
#ifdef __APPLE__
        const char* OSNAME = "Apple OS";
#else
        const char* OSNAME = "Unknown";
#endif
#endif
#endif 

int printShell();
char* getCommand();
char** splitCommand(char* InputCode);
int releaseMemory(char** CommandCode);

/**
 * @brief Main function
 * @details
 * Run other functions
 * @n Fork child process 
 * @n Execute given command
 * 
 * @return int 
 * Return 0 when the function ended successful
 * @n Return 1 when it isn't supported os
 */
int main()
{
    char* InputCode = NULL;
    //command* CommandCode = NULL;
    char** CommandCode = NULL;
    pid_t ProcessID = -1;

    if (strcmp(OSNAME, "Windows") == 0)
    {
        printf("This shell doesn't support Windows system. Will be exited in a second.\n");
        sleep(1000); // 1000ms -> 1s
        return 1;
    }

    while (1)
    {
        printShell();

        InputCode = getCommand();
        CommandCode = splitCommand(InputCode);

        if (CommandCode[0] == NULL)
        {
            continue;
        }
        if (strcmp(CommandCode[0], "exit") == 0)
        {
            break;
        }
        if (strcmp(CommandCode[0], "cd") == 0)
        {
            chdir(CommandCode[1]);
            continue;
        }

        ProcessID = fork();
        if (ProcessID != 0) 
        {
            // if running process is parent process, wait for child process
            int StatusValue = 0;
            pid_t ChildProcessID = wait(&StatusValue);
        }
        else
        {
            // if running process is child  process, execute given command
            execvp(CommandCode[0], CommandCode);
        }
    }

    releaseMemory(CommandCode);
    return 0;
}

/**
 * @fn printShell()
 * @brief Print shell interface, "Juhwan$"
 * 
 * @return int 
 * Return 0 when the function ended successfully
 */
int printShell()
{
    printf("Juhwan$ ");
    return 0;
}

/**
 * @fn getCommand()
 * @brief Get the Command string
 * 
 * @return char* 
 * Return string given from user
 * 
 * @see
 * This is an old Code, which had a problem.
 * @n It couldn't accpet input command without an option.
 * @n Because it was unable to 'skip' the second scanf format.
 * @code{.c}
 * //
 * char* _Name   = (char*)malloc(sizeof(char)*10);
 * char* _Option = (char*)malloc(sizeof(char)*10);
 *
 * scanf("%s %s", _Name, _Option);
 *
 * command* CommandCode = (command*)malloc(sizeof(command));
 * CommandCode->Name    = _Name;
 * CommandCode->Option  = _Option;
 * @endcode
 */
char* getCommand()
{
    const int BUFFER_SIZE = 128;
    char* InputCode = (char*)malloc(sizeof(char) * BUFFER_SIZE);
    char c;
    int ReAllocCount = 1;

    for (int i = 0; ; i++)
    {
        if (i == BUFFER_SIZE)
        {
            ReAllocCount++;
            InputCode = realloc(InputCode, sizeof(char) * BUFFER_SIZE * ReAllocCount);
            //printf("Given buffer size exceeded\n");
            //exit(1); //exit with an error code
        }

        c = getchar();

        if (c == '\n')
        {
            c = '\0';
            InputCode[i] = c;
            break;
        }
        else
        {
            InputCode[i] = c;
        }
    }
    return InputCode;
}

/**
 * @fn splitCommand(char* InputCode)
 * @brief Split string and make command struct
 * @details
 * Split string from getCommand()
 * 
 * @param InputCode 
 * Takes string from getCommand()
 * @return char**
 * Return a pointer of splited tokens.
 * @n This is an array of string pointers.
 * 
 * @see
 * This is an old Code, which had a problem.
 * @n It was okay with only one option.
 * @n So it was unable to execute a command like "diff file1 file2".
 * @code{.c}
 * command* CommandCode = (command*)malloc(sizeof(command)*1);
 * char SplitPoint = ' ';
 * 
 * //if user just pressed enter, no input
 * if (strcmp(InputCode, "\0") == 0)\
 * {
 *      CommandCode->Name = NULL;
 *      CommandCode->Option = NULL;
 *      return CommandCode;
 * }
 * 
 * CommandCode->Name = strtok(InputCode, &SplitPoint);
 * CommandCode->Option = strtok(NULL, &SplitPoint);
 * return CommandCode;
 * @endcode
 */
char** splitCommand(char* InputCode)
{
    const int BUFFER_SIZE = 32;
    int ReAlloc = 1;
    int Position = 0;
    char** CommandCode = (char**)malloc(sizeof(char*) * BUFFER_SIZE);
    char* Token;
    char SplitPoint = ' ';

    Token = strtok(InputCode, &SplitPoint);
    for (Position = 0; Token != NULL; Position++)
    {
        CommandCode[Position] = Token;

        if (Position >= BUFFER_SIZE * ReAlloc)
        {
            ReAlloc++;
            CommandCode = realloc(CommandCode, sizeof(char*) * BUFFER_SIZE * ReAlloc);
        }

        Token = strtok(NULL, &SplitPoint);
    }
    
    CommandCode[Position] = NULL;

    return CommandCode;
}

/**
 * @fn releaseMemory(char** CommandCode)
 * @brief Release used memory
 * 
 * @param CommandCode
 * Release a pointer, which was allocated by malloc()
 * @return int 
 * Return 0 when then function ended successfully
 * 
 */
int releaseMemory(char** CommandCode)
{
    free(CommandCode);

    return 0;
}