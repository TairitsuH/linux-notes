#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>


void task()
{
    sleep(1);
    printf("正在执行其他任务\n");
}


int main()
{
    pid_t ret = fork();
    if(ret < 0)
    {
        printf("创建失败\n");
        perror("fork");
        return 1;
    }
    else if(ret == 0)
    {
        printf("子进程：%d, 正在运行\n", getpid());
        sleep(5);
        int a = 1 / 0;
        //printf("子进程结束\n");
        //exit(5);
    }
    else
    {
        //阻塞等待
        //int st = 0;
        //printf("父进程：%d, 正在运行\n", getpid());
        //
        //int wret = wait(&st);
        //printf("阻塞等待结束\n");
        //
        ////正常退出
        //if(wret > 0 && (st & 0X7F) == 0)
        //{
        //    printf("子进程退出码：%d\n", (st >> 8) & 0XFF);
        //}
        //else if(wret > 0)
        //{
        //    printf("子进程异常退出\n);    
        //}
        //else
        //{
        //    printf("捕获子进程失败\n");
        //}
       
        //非阻塞等待
        int st = 0;
        printf("父进程：%d, 正在运行\n", getpid());
        
        pid_t wret = 0;

        do
        {
            task();
            wret = waitpid(ret, &st, WNOHANG);
            if(wret == 0) printf("子进程正在运行\n");
            sleep(1);
        }
        while(wret == 0);

        //宏：
        //WIFEXITED获取退出状态，非0正常退出，0为信号杀死（记图！）
        //WEXITSTATUS获取退出码（退出状态非0时有效

        //正常退出
        if(wret == ret && WIFEXITED(st))
        {
            printf("非阻塞等待结束\n");
            printf("子进程退出码：%d\n", WEXITSTATUS(st));
            return 0;
        }
        else if(wret > 0)
        {
            printf("子进程异常退出\n");    
            return 2;
        }
        else
        {
            printf("捕获子进程失败\n");
            return 1;
        }
    }
}
