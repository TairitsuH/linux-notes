#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
        sleep(1);
        int ret = fork();
        if(ret < 0) printf("创建失败\n");
        else if(ret == 0)
        {
        printf("我是子进程，我的标识符:%d，父进程标识符:%d，ret:%d\n", getpid(), getppid(), ret);
        }
        else
        {
        printf("我是父进程，我的标识符:%d，父进程标识符:%d，ret:%d\n", getpid(), getppid(), ret); 
        }
    return 0;
}
