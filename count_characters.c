#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

#define BUFFER_SIZE 2

void print_table(const long long *table)
{
    for(int i = 0;i < 255;i++)
        if(table[i])
        {
            if(i == '\n')
                 printf("charcter: new line  ----- > %d \n", table[i]);
            else
                printf("charcter: %c ----- > %d\n", i, table[i]);
        }
}

int read_file(int fd, char *buff, long long *table)
{

    while(1)
    {
        int read_status = read(fd, buff, BUFFER_SIZE);

        if(-1 == read_status)
        {
            printf("Read faild!!!\n");
            return -1;
        }

        if(!read_status)
            break;

        for(int i = 0;i < read_status;i++)
            table[buff[i]] ++;

    }
    return 0;
}


int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Not enough arguments given!!!\n");
        exit(1);
    }
    
    char *buff = malloc(BUFFER_SIZE);

    if(!buff)
        return 0;

    int fd = open(argv[1], O_RDONLY);
    if(fd == -1)
        return 0;

    long long tbl[255];

    for(int i = 0;i < 255;i++)
        tbl[i] = 0;

    read_file(fd, buff, tbl);
    print_table(tbl);
    return 0;
}

