#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

#define BUFFER_SIZE 2
int main(int argc, char **argv)
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
    
    char *buffer = malloc(BUFFER_SIZE * sizeof(*buffer));

    if(!buffer)
    {
        printf("Can't allocate memory!!!\n");
        close(file_descriptor);
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
            free(buffer);
            exit(4);
        }

        if(!read_status)
        {
            printf("Unable to read!!!\n");
            free(buffer);
            close(file_descriptor);
            exit(5);
        }

        int write_status = write(1, buffer, read_status);

        if(-1 == write_status)
        {
            printf("Write faild!!!\n");
            free(buffer);
            close(file_descriptor);
            exit(6);
        }

        if(0 == write_status)
        {
            printf("Write could not write to stdout");
            free(buffer);
            close(file_descriptor);
            exit(7);
        }
    
        iterator++;
    }

    printf("Success!!!\n");
    free(buffer);
    close(file_descriptor);
    exit(0);
}
