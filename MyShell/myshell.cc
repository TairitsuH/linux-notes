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
char cwd[1024];
char cwdenv[1024];
int exitcode = 0;

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
    // 不要用环境变量，因为进程路径先变环境变量再变，而shell内部会更新环境变量，而myshell没做更新工作
    // const char* pwd = getenv("PWD");
    const char* pwd = getcwd(cwd, sizeof(cwd));
    
    //导入环境变量
    if(pwd != NULL)
    {
        snprintf(cwdenv, sizeof(cwdenv), "PWD=%s", pwd);
        putenv(cwdenv);
    }
    return pwd == NULL ? "NONE" : pwd;
}

const char* GetHome()
{
    const char* home = getenv("HOME");
    return (home == NULL ? "" : home);
}

//获取当前目录名
string DirName(const char* pwd)
{
    #define SLASH "/"
    string dir = pwd;
    if(strcmp(pwd, SLASH) == 0) return SLASH;
    auto pos = dir.rfind(SLASH);
    if(pos == string::npos) return "BUG?";
    return dir.substr(pos + 1);
}

void MakeCommamdLine(char* cmd_prompt, int size)
{
    snprintf(cmd_prompt, size, FORMAT, GetUserName(), GetHostName(), DirName(GetPwd()).c_str());
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
    --g_argc; 
    return g_argc == 0 ? true : false;
}

void printargv()
{
    for(int i=0; g_argv[i]; ++i)
    {
        printf("argv[%d]->%s\n", i, g_argv[i]);
    }

    printf("argc:%d\n", g_argc);
}

//检测内建命令:对命令做判断
bool Cd()
{   
    if(g_argc == 1)
    {
        string home = GetHome();
        if(home.empty()) return true;
        chdir(home.c_str());
    }
    else 
    {
        string where = g_argv[1];
        if(where == "-")
        {
            //todo
        }
        else if(where == "~")
        {
            string home = GetHome();
            if(home == "") return true;
            chdir(home.c_str());
        }
        else
        {
            chdir(where.c_str());
        }
    }
    return true;
}

bool CheckAndExecBuiltin()
{
    string cmd = g_argv[0];
    if(cmd == "cd") //const char*要用strcmp比较！==仅仅比较地址！
    {
        Cd();
        return true;
    }
    else if(cmd == "echo")
    {
        //echo "hello world"
        //echo $?
        //echo $PATH
        if(g_argc == 2)
        {
            string op = g_argv[1];
            if(op == "$?")
            {
                cout << exitcode << endl;
            }
        }


        return true;
    }

    return false;
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
    
    int status = 0;
    //father
    pid_t rid = waitpid(pid, &status, 0);
    (void) rid; //使用一下
    
    if(rid > 0) exitcode = WEXITSTATUS(status);

    return exitcode;
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

        //4. 检测并处理内建命令
        if(CheckAndExecBuiltin())
        {
            continue; //不需要创建子进程
        }

        //4. 执行命令（fork，进程替换execvp
        Execute();

    }
        return 0;
}
