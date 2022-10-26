#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

#define BUFFER_SIZE 4096

void print_lines(int fd, int lines_count, char *buff)
{
    while(1)
    {
        int read_status = read(fd, buff, BUFFER_SIZE);

        if(!read_status)
            break;

        if(-1 == read_status)
        {
            printf("Read faild!!!\n");
            break;
        }
        
        int last_new_line_index = 0;
        for(int i = 0; i < read_status;i++)
        {
            if(buff[i] == '\n')
            {
                lines_count --;
                for(int j = last_new_line_index; j <= i; j++)
                {
                    last_new_line_index = i + 1;
                    printf("%c", buff[j]);
                }
            }

            if(!lines_count)
                break;
        }
    }
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

    if(argc == 2)
    {
        print_lines(file_descriptor, 10, buff);
    }

    else if(argc == 3)
    {
        if(!strcmp(argv[2], "0")) /// atoi retuns 0 for error, 0 is a valid number
        {
            free(buff); 
            close(file_descriptor);
            exit(0);
        }

        int lines = atoi(argv[2]);    
        if(lines <= 0) 
        {
            printf("This is not a valid number!!!\n");
            free(buff);
            close(file_descriptor);
            exit(4);
        }

        print_lines(file_descriptor, lines, buff);
    }
    
    free(buff); 
    close(file_descriptor);
    exit(0);
}
