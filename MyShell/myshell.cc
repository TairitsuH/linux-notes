#include<cwchar>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;

#define COMMAND_SIZE 1024
#define FORMAT "[%s@%s %s]# "
#define MAXARGC 128


char* g_argv[MAXARGC];
int g_argc = 0;

const char* GetUserName()
{
    const char* name = getenv("USER");
    return name == NULL ? "NONE" : name;
}

//const char* GetHostName(char hostname[], int size)
//{
//
//    gethostname(hostname, size);
//    return hostname;
//}

const char* GetPwd()
{
    const char* pwd = getenv("PWD");
    return pwd == NULL ? "NONE" : pwd;
}

//获取当前目录名
string DirName(const char* pwd)
{
    #define SLASH "/"
    string dir = pwd;
    if(pwd == SLASH) return SLASH;
    auto pos = dir.rfind(SLASH);
    if(pos == string::npos) return "BUG?";
    return dir.substr(pos + 1);
}

void MakeCommamdLine(char* cmd_prompt, int size)
{
    char s[5] = "tmp";
    snprintf(cmd_prompt, size, FORMAT, GetUserName(), s, DirName(GetPwd()).c_str());
}

void PrintCommandPrompt()
{
    char prompt[COMMAND_SIZE];
    MakeCommamdLine(prompt, sizeof(prompt));
    printf("%s", prompt);
    fflush(stdout);
}

bool GetCommandLine(char* out, int size)
{
    //获取命令行参数:ls -a -l -> "ls -a -l\n"字符串
    char* ret = fgets(out, size, stdin);
    if(!ret) return false;
    out[strlen(ret) - 1] = 0; //清理\n
    if(strlen(out) == 0) return false;
    return true;
}

//3. 命令行分割
bool CommandParse(char* commandline)
{
    #define SEP " "
    g_argc = 0;

    g_argv[g_argc++] = strtok(commandline, SEP);
    while((bool)(g_argv[g_argc++] = strtok(nullptr, SEP))); //继续分割不用重新传
    --g_argc; //
    return true;
}

void printargv()
{
    for(int i=0; g_argv[i]; ++i)
    {
        printf("argv[%d]->%s\n", i, g_argv[i]);
    }

    printf("argc:%d\n", g_argc);
}

//4. 执行命令
int Execute()
{
    pid_t pid = fork();
    if(pid < 0) exit(1);
    if(pid == 0) //child
    {
        execvp(g_argv[0], g_argv);
        exit(1);
    }   
    else //father
    {
        pid_t rid = waitpid(pid, nullptr, 0);
        (void) rid; //使用一下
    }

    return 0;
}


int main()
{
    while(1)
    {
        //1. 输出命令行提示符
        PrintCommandPrompt();
        
        //2. 获取用户输入命令
        char commandline[COMMAND_SIZE];
        if(!GetCommandLine(commandline, sizeof(commandline)))
        {
            continue;
        }

        //printf("echo %s\n", commandline);

        //3. 命令行分割
        CommandParse(commandline);
        //printargv();

        //4. 执行命令（fork，进程替换execvp
        Execute();

    }
        return 0;
}
