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

/**
 * @struct STcommand
 * @brief Contain execution command name and its option
 */
typedef struct STcommand
{
    /**
     * @var char* Name
     * Command (ex. ls, cd...)
     */
    char* Name;
    /**
     * @var char* Option
     * Option of the command (ex. -rf from "rm -rf")
     */
    char* Option;
}command;

int printShell();
char* getCommand();
command* splitCommand(char* _InputCode);
int releaseMemory(command* _CommandCode);

/**
 * @brief Main function
 * @details
 * Run other functions
 * @n Takes keyboard input from user
 * @n Execute given command
 * 
 * @return int 
 * Return 0 when the function ended successful
 * @n Return 1 when it isn't supported os
 */
int main()
{
    char* InputCode = NULL;
    command* CommandCode = NULL;
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

        if (CommandCode->Name == NULL)
            continue;
        if (strcmp(CommandCode->Name, "exit") == 0)
            break;

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
            if (CommandCode->Name != NULL)
                execlp(CommandCode->Name, CommandCode->Name, CommandCode->Option, 0);
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
 * command* _CommandCode = (command*)malloc(sizeof(command));
 * _CommandCode->Name    = _Name;
 * _CommandCode->Option  = _Option;
 * @endcode
 */
char* getCommand()
{
    const int BUFFER_SIZE = 256;
    char* _InputCode = (char*)malloc(sizeof(char)*BUFFER_SIZE);
    char c;

    for (int i = 0; ; i++)
    {
        if (i == BUFFER_SIZE)
        {
            printf("Given buffer size exceeded\n");
            exit(1); //exit with an error code
        }

        c = getchar();

        if (c == '\n')
        {
            c = '\0';
            _InputCode[i] = c;
            break;
        }
        else
        {
            _InputCode[i] = c;
        }
    }
    return _InputCode;
}

/**
 * @fn splitCommand(char* _InputCode)
 * @brief Split string and make command struct
 * @details
 * Split string from getCommand()
 * @n as command name and command option
 * @n then make a STcommand instance with splited data
 * @n filally return it
 * 
 * @param _InputCode 
 * Takes string from getCommand()
 * @return command* 
 * Return a pointer of command struct
 * 
 * @see
 * @ref STcommand
 * Using this struct
 */
command* splitCommand(char* _InputCode)
{
    command* _CommandCode = (command*)malloc(sizeof(command)*1);
    char SplitPoint = ' ';

    //if user just pressed enter, no input
    if (strcmp(_InputCode, "\0") == 0)\
    {
        _CommandCode->Name = NULL;
        _CommandCode->Option = NULL;
        return _CommandCode;
    }
    
    _CommandCode->Name = strtok(_InputCode, &SplitPoint);
    _CommandCode->Option = strtok(NULL, &SplitPoint);
    
    return _CommandCode;
}

/**
 * @fn releaseMemory(command* _CommandCode)
 * @brief Release used memory
 * 
 * @param _CommandCode
 * Release this struct and its member, which was allocated by malloc()
 * @return int 
 * Return 0 when then function ended successfully
 * 
 * @see
 * @ref STcommand
 * Refer to this struct
 */
int releaseMemory(command* _CommandCode)
{
    if(_CommandCode->Name != NULL)
        free(_CommandCode->Name);
    if(_CommandCode->Option != NULL)
        free(_CommandCode->Option);

    free(_CommandCode);

    return 0;
}