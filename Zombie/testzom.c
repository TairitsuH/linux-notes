#include<stdio.h>
#include<unistd.h>
#include<stdlib.h> //exit
#include<sys/types.h>

//测试僵尸进程：子退出，父未回收
int main()
{
    pid_t ret = fork();
    if(ret < 0)
    {
        perror("fork()");
        exit(1);
    }

    if(ret == 0) //创建成功
    {
        //子进程
        printf("子进程：%d\n", getpid());
        sleep(3);
        printf("子进程结束\n");
        exit(0);
    }
    else
    {
        printf("我是父进程%d，我的子进程是：%d\n", getpid(), ret);
        printf("parent is sleeping...\n");
        sleep(60); 
    }
    
    return 0;
}
