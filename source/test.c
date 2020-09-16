#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const int BUFFER_SIZE = 20;
    char* InputCode = (char*)malloc(sizeof(char)*BUFFER_SIZE);
    char c;

    for(int i = 0; 0; i++)
    {
        c = getchar();
        if(c == '\n')
        {
            c = '\0';
            InputCode[i] = c;
            break;
        }
        InputCode[i] = c;
    }

    printf("FUCK!\n");

    return 0;
}