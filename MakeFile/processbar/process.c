#include "process.h"
#include<string.h>
#include<unistd.h>

#define NUM 101
#define STYLE '#'

void FlushProcess(double total, double current) //一次打印
{
    char buffer[NUM];
    memset(buffer, '-',sizeof(buffer));
    const char* lable = "|/-\\";
    int len = strlen(lable);

    static int cnt = 0; //lable下标：静态是为了能不间断旋转
    int num = (int)(current * 100) / total; //下载进度（需要加载多少个#
    for(int i=0; i<=num; ++i)
    {
        buffer[i] = STYLE;
    }

    double rate = current / total; //下载进度（比率
    cnt %= len;
    printf("[%-100s][%.1f%%][%c]\r", buffer, rate * 100, lable[cnt]);
    ++cnt;

    fflush(stdout);
}

//无法使用，伪进度条
void process_v1()
{
    char buffer[NUM];
    const char* lable = "|/-\\";
    int len = strlen(lable);
    memset(buffer, 0, sizeof(buffer));

    int cnt = 0;
    while(cnt <= 100)
    {
        printf("[%-100s][%d%%][%c]\r", buffer, cnt, lable[cnt%len]);
        buffer[cnt] = STYLE;

        fflush(stdout);
        usleep(50000);
        ++cnt;
    }

    printf("\n");
}

//测试修改