#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

#define BUFFER_SIZE 4096

long long count_lines(int fd, char *buff)
{
    unsigned long long new_lines = 0;

    while(1)
    {
        int read_status = read(fd, buff, BUFFER_SIZE); 
        
        if(!read_status) 
            break;

        if(-1 == read_status)
        {
            printf("Read faild!!!\n");
            return -1;
        }
    

        for(int i = 0;i < read_status;i++)
            new_lines += (buff[i] == '\n');
    }

    if(lseek(fd, 0,  SEEK_SET) == -1)
    {
        printf("lseek faild!!!\n");
        return -1;
    }
    
    return new_lines;
}

long long count_bytes(int fd, char *buff)
{
    long long bytes = 0;
    while(1)
    {
        int read_status = read(fd, buff, BUFFER_SIZE);

        if(!read_status)
            break;

        if(-1 == read_status)
        {
            printf("Read faild!!!\n");
            return -1;
        }

        bytes += read_status;
    }
    
    if(lseek(fd, 0, SEEK_SET) == -1)
    {
        printf("lseek faild!!!\n");
        return -1;
    }

    return bytes;
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Not enough arguments given!!!\n");
        exit(1);
    }
    
    int file_descriptor = open(argv[1], O_RDONLY);
    if(-1 == file_descriptor)
    {
        printf("Unable to open given file!!!\n");
        exit(2);
    }
    
    char *buff = malloc(BUFFER_SIZE * sizeof(*buff));
    
    if(!buff)
    {
        printf("Can't allocate memory!!!\n");
        close(file_descriptor);
        exit(3);
    }
    
    if(2 == argc)
    {
        long long c_l = count_lines(file_descriptor, buff);
        long long c_b = count_bytes(file_descriptor, buff);
        
        if(c_l == -1 || c_b == -1)
        {
            printf("Error");
            exit(5);
        }

        printf("%d\n", c_l);
        printf("%d\n", c_b);
    }

    if(3 <= argc)
    {
        long long c_l = count_lines(file_descriptor, buff);
        long long c_b = count_bytes(file_descriptor, buff);
        
        if(c_l == -1 || c_b == -1)
        {
            printf("Error");
            exit(5);
        }

        if(!strcmp(argv[2], "-l"))
            printf("%d\n", c_l);

        else if(!strcmp(argv[2] , "-c"))
            printf("%d\n", c_b);
        
        else
        {
            printf("This operation is unknown!!!\n");
            exit(6);
        }
    }
    if(4 == argc)
    {
        long long c_l = count_lines(file_descriptor, buff);
        long long c_b = count_bytes(file_descriptor, buff);
        
        if(c_l == -1 || c_b == -1)
        {
            printf("Error");
            exit(5);
        }

        if(!strcmp(argv[3], "-l"))
            printf("%d\n", c_l);

        else if(!strcmp(argv[3] , "-c"))
            printf("%d\n", c_b);
        
        else
        {
            printf("This operation is unknown!!!\n");
            exit(6);
        }
    }

    free(buff);
    close(file_descriptor);
    exit(0);
}
