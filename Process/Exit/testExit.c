#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    printf("hello");
    exit(0); //库刷新缓冲区
    
    sleep(3);
    // _exit(0); //系统调用不会刷新缓冲器
    

    return 0; //作用相当于exit
}
