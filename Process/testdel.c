#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    chdir("/home/yun");
    while(1)
    {
        sleep(1);
        printf("%d:正在运行子进程\n", getpid());
    }
    return 0;
}
