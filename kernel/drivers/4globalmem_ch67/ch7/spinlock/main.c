#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
main()
{
    int fd;
    fd = open("/dev/spinlocktest",O_RDWR);
    if(fd<0)
    {
        perror("open fail \n");
        return;
    }
    sleep(20);
    close(fd);   
    printf("open ok \n ");
}