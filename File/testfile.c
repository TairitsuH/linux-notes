#include <stddef.h>
#include<stdio.h>
#include<string.h>

int main()
{
    // 测试接口
    FILE* fp = fopen("log.txt", "w+"); //读写状态打开
    if(!fp)
    {
        printf("fopen error!\n");
        return 1;
    }
    
    printf("open successfully!\n");

    char buf[1024];
    const char* msg = "helloworld!helloworld!\0";

    //写入：从msg地址开始连续写入1*strlen字节
    size_t retw =  fwrite(msg, strlen(msg), 1, fp); //返回写入的字节数
    fflush(fp); //强制刷新缓冲区
    if(retw > (size_t)0) printf("写入完成，共写入%zu个字节\n", retw*strlen(msg) );
    else
    {
        printf("写入失败\n");
        return 1;
    }

    //重置光标
    rewind(fp);
        
    size_t cnt = 0;
    while(1)
    {
        //读取：成功返回读取到的字节数/失败或读取结束返回0
        size_t retr = fread(buf + cnt, 1, strlen(msg), fp);
        if(retr > 0)
        {
            cnt += retr;
            printf("读取文件中...\n");
        }
        else if(feof(fp))
        {
            buf[cnt] = 0;
            printf("全文件读取结束，共读取%zu个字节\n", cnt);
            break;
        }
        else
        {
            printf("读取出错\n");
            return 1;
        }
    }

    printf("读取到的内容为：%s\n", buf);

    fclose(fp);
    return 0;
}
