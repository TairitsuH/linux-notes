#ifndef __PROCESS_POOL_HPP__
#define __PROCESS_POOL_HPP__

#include<iostream>
#include<vector>
#include<sys/types.h>
#include<unistd.h>

//单信道
class Channel
{
private:
    int _wfd; //写端fd

public:
    Channel(){}
    ~Channel(){}
};

//信道管理
class ChannelManager
{
private:
    std::vector<Channel> _channels;

public:
    ChannelManager(){}
    ~ChannelManager(){}
};

//进程池
class ProcessPool
{
private:
    ChannelManager _cm;
    int _process_num;

public:
    ProcessPool(int num)
    :_process_num(num)
    {}

    ~ProcessPool(){}

    //创建进程池
    bool Create()
    {
        int pipefd[2] = {0};
        pid_t id = fork();
        if(id < 0)
        {
            return false;
        }
        if(id == 0) //child
        {
            close(pipefd[1]);
            Work(pipefd[0]);
            close(pipefd[0]);
            exit(0);
        }
        
        //parent
        close(pipefd[0]);

        //多进程
        //for(int i=0; i<_process_num; ++i)
    }

    return true;
};

void Work(int rfd)
{
    while(true)
    {
        std::cout << "我是子进程，我的rfd是：" << rfd << std::endl;
        sleep(1);
    }
}

void Debug()
{
    
}



#endif