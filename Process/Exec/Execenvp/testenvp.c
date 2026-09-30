#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    printf("testenvp正在运行\n");
    char* path = getenv("PATH");
    char* term = getenv("TERM");
    if(path)
    {
        printf("PATH=%s\n", path);
    }
    if(term)
    {
        printf("TERM=%s\n", term);
    }
    return 0;
}
