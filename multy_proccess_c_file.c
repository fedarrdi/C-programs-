#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/mman.h>

#define BUFFER_SIZE 2


void print_table(const long long  *table)
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
        
        if(lseek(fd, BUFFER_SIZE, SEEK_CUR) == -1)
            return -1;
    }
    return 0;
}

int fork_run(char *name)
{
    
    long long *shared_memory = mmap(NULL, 255 * sizeof *shared_memory,
                                   PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED,
                                   -1, 0);
    if(!shared_memory)
    {
        printf("ERROR\n");
        return -1;
    }

    if(fork() == 0)
    {
    
        char *buff = malloc(BUFFER_SIZE * sizeof(*buff));

        if(!buff) return -1;

        int fd = open(name, O_RDONLY);

        if(fd == -1) return -1;
    
        if(read_file(fd, buff, shared_memory) == - 1) return -1;
        
        free(buff);
        close(fd);
    }

    else
    {
        char *buff = malloc(BUFFER_SIZE * sizeof(*buff));

        if(!buff) return -1;

        int fd = open(name, O_RDONLY);
        
        if(lseek(fd, BUFFER_SIZE, SEEK_SET) == -1) return -1;

        if(fd == -1) return -1;
    
        if(read_file(fd, buff, shared_memory) == - 1) return -1;
    
        free(buff);
        close(fd);
    }

    printf("hello\n"); 
    print_table(shared_memory); 
    

    munmap(shared_memory, 255 * sizeof *shared_memory);
    return 0;
}


int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Not enough arguments given!!!\n");
        exit(1);
    }
    
    fork_run(argv[1]);

    return 0;
}
