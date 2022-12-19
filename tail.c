#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<math.h>

#define BUFFER_SIZE 4

long long get_file_size(int fd) 
{
    long long size = lseek(fd, 0, SEEK_END);
    if(lseek(fd, 0, SEEK_SET) == -1) return -1;
    return size;
}

long long find_start_byte(int fd, int lines, char *buff)
{
    int file_size = get_file_size(fd);
    
    if(file_size == -1)
    {
        printf("lseek faild!!!\n");
        return -1;
    }

    if(lseek(fd, 0, SEEK_END) == -1)
    {
        printf("lseek faild!!!\n");
        return -1;
    }
    
    for(long long offset = 1; offset < file_size; ++offset)
    {
        if(lseek(fd, -1 * offset, SEEK_END) == -1)
        {
            printf("lseek faild!!!\n");
            return -1;
        }
        int read_status = read(fd, buff, 1);

        if(!read_status)
            return 0;

        if(read_status == -1)
        {
            printf("read faild!!!\n");
            return -1;
        }

        lines -= (buff[0] == '\n');
        
        if(lines == -1)
            return file_size - offset + 1;
        
    }
    return 0;
}

int print_lines(int fd, int lines, char *buff)
{
    long long offset = find_start_byte(fd, lines, buff);

    if(offset == -1)
        return -1;
    
    if(lseek(fd, offset, SEEK_SET) == -1)
    {
        printf("lseek faild!!!\n");
        return -1;
    }

    while(1)
    {
        int read_status = read(fd, buff, BUFFER_SIZE);
    
        if(!read_status)
            break;

        if(read_status == -1)
        {
            printf("read faild!!!\n");
            return -1;
        }

       for(int i = 0;i < read_status;i++)
            printf("%c", buff[i]);
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
    
    if(argc == 3)
    {
        printf("Not enough arguments!!!\n");
        free(buff);
        close(file_descriptor);
        exit(4);
    }

    if(argc == 4)
    {

        if(strcmp(argv[2], "-n"))
        {
            printf("%s command doesn't exist\n", argv[2]);
            free(buff);
            close(file_descriptor);
            exit(5);
       }

        if(!strcmp(argv[3], "0")) /// atoi retuns 0 for error, 0 is a valid number
        {
            free(buff); 
            close(file_descriptor);
            exit(0);
        }

        int lines = atoi(argv[3]);    
        if(lines <= 0) 
        {
            printf("This is not a valid number!!!\n");
            free(buff);
            close(file_descriptor);
            exit(6);
        }

        print_lines(file_descriptor, lines, buff);
    }
    
    free(buff); 
    close(file_descriptor);
    exit(0);
}
