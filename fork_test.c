#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/mman.h>

#define BUFFER_SIZE 2

int NUMBER_OF_PROCESES = 0;

void print_table(const long long *table, int procces)
{
    if(procces != NUMBER_OF_PROCESES - 1) return;

    for(int i = 0;i < 255;i++)
        if(table[i])
        {         
            if(i == '\n')
                 printf("charcter: new line  ----- > %d \n", table[i]);
            else
                printf("charcter: %c ----- > %d\n", i, table[i]);
        }
}

int read_file(char *name, int offset, long long *tbl)
{
    int RETURN_VALUE = 0, fd = open(name, O_RDONLY); 
    if(fd == -1) return -1;

    unsigned char *buff = malloc(sizeof *buff * BUFFER_SIZE);

    if(!buff)
    {
        close(fd);
        return -1;
    }

    if(lseek(fd, BUFFER_SIZE * offset, SEEK_SET) == -1)
    {
        printf("lseek faild!!!\n");
        free(buff);
        close(fd);
        return -1;
    }
    
    while(1)
    {
        int read_status = read(fd, buff, BUFFER_SIZE);

        if(-1 == read_status)
        {
            printf("Read faild!!!\n");
            RETURN_VALUE = -1;
            break;
        }

        if(!read_status) break;
        
        for(int i = 0;i < read_status; tbl[buff[i++]] ++);    

        if(lseek(fd, BUFFER_SIZE * (NUMBER_OF_PROCESES - 1), SEEK_CUR) == -1)
        {
            RETURN_VALUE = -1;
            break;
        }
    }

    free(buff);
    close(fd);
    return RETURN_VALUE;
}

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        printf("Not enough arguments!!!\n");
        exit(1);
    }
    
    NUMBER_OF_PROCESES = atoi(argv[2]);

    long long *tbl = mmap(NULL, 255 * sizeof *tbl,
                                   PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED,
                                   -1, 0);

    if(!tbl)
    {
        printf("ERROR");
        exit(2);
    }

    for(int i = 0;i < 255; ++i)
        tbl[i] = 0;

    for(int i = 0;i < NUMBER_OF_PROCESES; ++i)
        if(fork() == 0)
        {
            if(read_file(argv[1], i, tbl) == -1)
                printf("procces: %d ----> FAILD!!!\n", getpid()); 
            
            print_table(tbl, i);
            break;
        }
    


    munmap(tbl, 255 * sizeof *tbl);
    exit(0);
}
