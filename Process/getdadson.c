#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    printf("pid:%d\n", getpid()); //获取子进程
    printf("ppid:%d\n", getppid()); //获取父进程
    return 0;
}
