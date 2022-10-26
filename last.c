#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

#define BUFFER_SIZE 2


long long table[255];


void update_table(char *buff, int bytes_count)
{
    for(int i = 0;i < bytes_count;i++)
        table[buff[i]]++;
} 

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        printf("Not enough arguments given!!!\n");
        exit(1);
    }
    
    int file_descriptor = open(argv[1], O_RDONLY);
    int file_new = open(argv[2], O_WRONLY | O_TRUNC);

    if(-1 == file_descriptor || -1 == file_new)
    {
        printf("Unable to open given files!!!\n");
        exit(2);
    }


    char *buffer = malloc(BUFFER_SIZE * sizeof(*buffer));
    
    if(!buffer)
    {
        printf("Can't allocate memory!!!\n");
        close(file_descriptor);
        close(file_new);
        exit(3);
    }

    int iterator = 0;
    while(1)
    {
        int read_status = read(file_descriptor, buffer, BUFFER_SIZE); 
        
        if(iterator && !read_status)
            break;
        
         if(-1 == read_status)
        {
            printf("Read faild!!!\n");
            close(file_descriptor);
            close(file_new);
            free(buffer);
            exit(4);
        }

        if(!read_status)
        {
            printf("Unable to read!!!\n");
            free(buffer);
            close(file_new);
            close(file_descriptor);
            exit(5);
        }
        
        update_table(buffer, read_status);
        iterator++;
    }

    free(buffer);
    close(file_descriptor);

    for(int i = 0;i < 255;i++)
    {
        char *in = malloc(table[i]);
        if(!in)
        {
            printf("not able to allocate memory!!!\n\n");
            close(file_new);
            exit(3);
        }
        memset(in, 97, table[i]);
        
        int write_status = write(file_new, in, 1);
        free(in);    
        if(-1 == write_status)
        {
            printf("Write faild!!!\n");
            close(file_new);
            exit(6);
        }   

        if(0 == write_status)
        {
            printf("Write could not write in file!!!\n");
            close(file_new); 
            exit(7);
        }
    }

    printf("Success!!!\n");
    close(file_new);
    exit(0);
}
