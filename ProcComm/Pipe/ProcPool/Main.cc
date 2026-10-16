#include<iostream>
#include<ProcessPool.hpp>

int gdefaultnum = 5;

int main()
{
    //1.创建进程池对象
    ProcessPool pp(gdefaultnum);
    pp.Create();
    pp.Debug();




    //2.启动进程池

    //3.分配任务

    //4.结束，回收fd和等待子进程退出


    return 0;
}