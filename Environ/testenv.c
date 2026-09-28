#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char *argv[], char *env[])
{
    //命令行参数表测试
    // for(int i=0; i<argc; ++i)
    // {
    //     printf("argv[%d]: %s\n", i, argv[i]);
    // }
    //
    
    //父子进程虚拟地址测试
    int g_val = 100;
    pid_t ret = fork();
    if(ret < 0) perror("fork");
    if(ret == 0)
    {
        printf("这里是子进程%d, g_val = %d, 虚拟地址 = %p\n", getpid(), g_val, &g_val);

        g_val = 200;

        printf("这里是子进程%d, g_val = %d, 虚拟地址 = %p\n", getpid(), g_val, &g_val);
        sleep(3);
    }
    else
    {
        printf("这里是父进程%d, g_val = %d, 虚拟地址 = %p\n", getpid(), g_val, &g_val);
        
        sleep(3);

        printf("这里是父进程%d, g_val = %d, 虚拟地址 = %p\n", getpid(), g_val, &g_val);

        int status;
        wait(&status);
    }

    return 0;
}
