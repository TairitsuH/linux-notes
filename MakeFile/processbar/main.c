#include"process.h"
#include<unistd.h>

double total = 1024.0;
double speed = 1.0;

typedef void (*callback_t)(double total, double current);

void Download(callback_t cb)
{
    double current = 0;
    while(current <= total)
    {
        cb(total, current);

        usleep(3000);
        current += speed;
    }

    printf("\ndownload %.2lfMB Done\n", current);
}

void Upload(callback_t cb)
{
    double current = 0;                          
    while(current <= total)                      
    {                                            
        cb(total, current);                      
                                                 
        usleep(3000);                            
        current += speed;                        
    }                                            
                                                 
    printf("\nupload %.2lfMB Done\n", current);
}


int main()
{
    Download(FlushProcess);
    Download(FlushProcess);
    Download(FlushProcess);

    Upload(FlushProcess);
    Upload(FlushProcess);
    Upload(FlushProcess);

    return 0;
}
