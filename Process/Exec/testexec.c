#define _GNU_SOURCE //execvpe在特性测试宏中
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

char* const argv[] = {"ps", "-ef", NULL};
char* const myargv[] = {"/home/yun/linux-notes/Process/Exec/Execenvp/testenvp", NULL};
char* const envp[] = {"PATH=/bin:/usr/bin", "TERM=hello,world!", NULL};

int main()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("子进程：%d\n", getpid());
        // execl("/bin/ls", "bin/ls", "-l", "-a", NULL); //列表+全路径
        // perror("execl");
        // execlp("ps", "ps", "-e", "-f", NULL); //列表+PATH环境变量
        // perror("execlp");
        // execle("/home/yun/linux-notes/Process/Exec/Execenvp/testenvp", "/home/yun/linux-notes/Process/Exec/Execenvp/testenvp",  NULL, envp);
        // perror("execle");
        // execv("/bin/ps", argv);
        // perror("execv");
        // execvp("ps", argv);
        // perror("execv");
        // execve("/home/yun/linux-notes/Process/Exec/Execenvp/testenvp", myargv, envp); //系统调用
        // perror("execve");
        execvpe("ps", argv, envp);
        perror("execvpe");
        exit(127);

    }
    else
    {
        sleep(1);
        printf("父进程：%d\n", getpid());
        int status;
        pid_t ret = wait(&status);
    }
    return 0;
}
