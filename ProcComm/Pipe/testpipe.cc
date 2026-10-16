#include <ctime>
#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

void ChildWrite(int wfd)
{
    char buffer[1024]; 
    int cnt = 0;

  while(true)
  {
    snprintf(buffer, sizeof(buffer), "我是子进程，pid:%d, cnt:%d", getpid(), cnt++);
    write(wfd, buffer, strlen(buffer));
    sleep(1);
  }
}

void ParentRead(int rfd)
{
    char buffer[1024];
    while(true)
    {
        buffer[0] = 0; //设置0防止打印出错
        ssize_t n = read(rfd, buffer, sizeof(buffer) - 1);
        if(n > 0)
        {
            buffer[n] = 0;
            std::cout << "child say: " << buffer << std::endl;
        }
    }
}

int main()
{
    //1.创建管道
    int fds[2] = {0};
    int n = pipe(fds); //开辟缓冲区（大小64KB），返回读写端fd
    if(n < 0) //0成功，-1失败
    {
        std::cerr << "pipe error" << std::endl;
        return 1;
    }

    //2.创建子进程
    pid_t id = fork();
    if(id == 0) //child
    {
        close(fds[0]);
        ChildWrite(fds[1]);
        close(fds[1]);
        exit(0);
    }

    //parent
    close(fds[1]);
    ParentRead(fds[0]);
    waitpid(id, nullptr, 0);
    close(fds[0]);
    
    // std::cout << "fds[0]:" << fds[0] << std::endl;
    // std::cout << "fds[1]:" << fds[1] << std::endl;

    return 0;
}
