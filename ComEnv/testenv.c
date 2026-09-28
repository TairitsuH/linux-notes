#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>


int main(int argc, char *argv[], char *env[])
{
    //命令行参数表测试
    // for(int i=0; i<argc; ++i)
    // {
    //     printf("argv[%d]: %s\n", i, argv[i]);
    // }
    //
    
    //父子进程虚拟地址测试
   // int g_val = 100;
   // pid_t ret = fork();
   // if(ret < 0) perror("fork");
   // if(ret == 0)
   // {
   //     printf("这里是子进程%d, g_val = %d, 虚拟地址 = %p\n", getpid(), g_val, &g_val);

   //     g_val = 200;

   //     printf("这里是子进程%d, g_val = %d, 虚拟地址 = %p\n", getpid(), g_val, &g_val);
   //     sleep(3);
   // }
   // else
   // {
   //     printf("这里是父进程%d, g_val = %d, 虚拟地址 = %p\n", getpid(), g_val, &g_val);
   //     
   //     sleep(3);

   //     printf("这里是父进程%d, g_val = %d, 虚拟地址 = %p\n", getpid(), g_val, &g_val);

   //     int status;
   //     wait(&status);
   // }
        
   
   //导入环境变量，可以直接testenv运行：export PATH=$PATH:/home/yun/linux-notes/ComEnv

    //通过env获取环境变量
    //printf("这是从环境变量表中打印的\n");

    //for(int i=0; env[i]; ++i)
    //{
    //    printf("%s\n", env[i]);
    //}
    //
    //printf("\n");

    //printf("这是通过全局指针environ打印的\n");
    //extern char** environ;
    //for(int i=0; environ[i]; ++i)
    //{
    //    printf("%s\n", environ[i]);
    //}

    //通过系统调用设置/获取环境变量
    //printf("%s\n", getenv("PATH"));

    
    //全局属性
    //export MYENV="hello world"
    char* myenv = getenv("MYENV");
    if(myenv)
    {
        printf("%s\n", myenv);
    }



    return 0;
}
