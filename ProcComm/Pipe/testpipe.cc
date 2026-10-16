#include<iostream>
#include<unistd.h>

int main()
{
    int fds[2] = {0};
    int n = pipe(fds);
    if(n < 0) //0成功，-1失败
    {
        std::cerr << "pipe error" << std::endl;
        return 1;
    }
    
    std::cout << "fds[0]:" << fds[0] << std::endl;
    std::cout << "fds[1]:" << fds[1] << std::endl;

    return 0;
}
