#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    pid_t ret = fork();

    if(ret < 0)
    {
        perror("fork()");
        return 1;
    }

    //const char*不可修改指针内容，char* const不可修改指针指向
    char* const g_argv[] = {"ls", "-l", "-a", NULL};
    char* const envp[] = {"PATH=/bin:/yun/bin", "TERM=console", NULL};

    //子进程
    if(ret == 0)
    {
        sleep(1);
        printf("i'm child, my pid:%d, ppid:%d\n", getpid(), getppid());
        //进程替换
        execl("/bin/ls", "/bin/ls", "-l", "-a", NULL); 
        //execlp("ls", "ls", "-l", "-a", NULL); //带p默认PATH
        extern char** environ;
        //待修改execle("ps", "ps", "-ef",  NULL, envp); //带e的传入环境变量


        //待修改execv("bin/ps", g_argv);
        //execvp("ls", g_argv);
       // execvpe("./other", g_argv, envp);

        //系统调用
        //execve("bin/ls", g_argv, envp);

        printf("被覆盖的代码\n");
    }
    else //父进程
    {
        printf("i 'm parent, my pid:%d, my child's pid:%d\n", getpid(), ret);
        
        sleep(5);
        int* status;
        pid_t p = wait(status);

        
    }
    return 0;
}
