#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

const char* GetUserName()
{
    const char* name = getenv("USER");
    return name == NULL ? "NONE" : name;
}

const char* GetHostName()
{
    const char* hostname = getenv("HOSTNAME");
    return hostname == NULL ? "NONE" : hostname;
}

const char* GetPwd()
{
    const char* pwd = getenv("PWD");
    return pwd == NULL ? "NONE" : pwd;
}

int main()
{
    printf("[%s@%s %s]#", GetUserName(), GetHostName(), GetPwd());
    
    return 0;
}
