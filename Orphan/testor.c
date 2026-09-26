#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

//孤儿进程验证：父进程先退出，子进程被os捕获
int main()
{
    pid_t ret = fork();
    if(ret < 0)
    {
        perror("fork()");
        exit(1);
    }

    if(ret == 0)
    {
        printf("child:%d, my parent is:%d, i am sleeping...\n", getpid(), getppid());
        sleep(10);
        printf("child:%d, my parent is: %d\n", getpid(), getppid());
        sleep(20);
    }
    else
    {
        printf("parent:%d, my child is:%d, parent exit now\n", getpid(), ret);
        return 0;
    }
    return 0;
}
