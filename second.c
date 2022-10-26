#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

#define BUFFER_SIZE 3

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        printf("Not enough arguments given!!!\n");
        exit(1);
    }

    int file_a = open(argv[1], O_RDONLY);
    int file_b = open(argv[2], O_WRONLY | O_TRUNC);

    if(-1 == file_a || -1 == file_b)
    {
        printf("Unable to open given files!!!\n");
        exit(2);
    }

    char *buffer = malloc(BUFFER_SIZE * sizeof(*buffer));

    if(!buffer)
    {
        printf("Can't allocate memory!!!\n");
        close(file_a);
        close(file_b);
        exit(3);
    }
    
    int iterator = 0; 

    while(1)
    {
    
        int read_status = read(file_a, buffer, BUFFER_SIZE);
    
        if(iterator && !read_status)
            break;

        if(-1 == read_status)
        {
            printf("Read faild!!!\n");
            close(file_a);
            close(file_b);
            free(buffer);
            exit(4);
        }

        if(!read_status)
        {
            printf("Unable to read!!!\n");
            free(buffer);
            close(file_a);
            close(file_b);
            exit(5);
        }


        int write_status = write(file_b, buffer, read_status);

        if(-1 == write_status)
        {
            printf("Write faild!!!\n");
            free(buffer);
            close(file_a);
            close(file_b);
            exit(6);
        }

        if(0 == write_status)
        {
            printf("Write could not write to stdout!!!\n");
            free(buffer);
            close(file_a);
            close(file_b); 
            exit(7);
        }

        iterator++;
    }

    printf("Success!!!\n");
    close(file_a);
    close(file_b);
    free(buffer);

    exit(0);
}
