#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

#define BUFFER_MAIN_READ_SIZE  8*sizeof(uint8_t) + 2*sizeof(uint32_t)

void get_data(char *buffer, uint8_t *name, uint32_t *offset, uint32_t *length)
{
    for(int i = 0;i < 8;i++)
        *(name + i) = *(buffer + i);
    buffer += 8;
    *offset = *(uint32_t*)buffer;
    buffer += sizeof(*offset);
    *length = *(uint32_t*)buffer;
    buffer -= sizeof(*offset) + 8;
}

long long read_child_file_get_xor(int child_file_descriptor, uint32_t length)
{
    uint16_t buffer, xor;
    int in_flag = 0;
    
    for(;length; length--)
    {
        int read_status = read(child_file_descriptor, &buffer, sizeof(buffer));
        
        if(read_status == -1)
        {
            printf("Child file read faild!!!\n");
            return -1;
        }

        if(!read_status) return -1;
        
        if(!in_flag) 
        {
            xor = buffer;
            in_flag = 1; 
        }
        
        else
        {
            xor ^= buffer;
        }
    }
     
    if(length) return -1;

    return xor;

}

long long open_file_get_xor(char *file_name , uint32_t offset, uint32_t length)
{
    int child_file_descriptor = open(file_name, O_RDONLY);
    if(!child_file_descriptor)
    {
        printf("Can't open file!!!\n");
        return -1;
    }

    if(lseek(child_file_descriptor, offset, SEEK_SET) == -1)
    {
        printf("Lseek faild!!!\n");
        return -1;
    }

    int xor = read_child_file_get_xor(child_file_descriptor, length);
    if(xor == -1)
    {
        printf("%s: read faild\n", file_name);
        return -1;
    }

    close(child_file_descriptor);
    return xor;
}

int read_main_file(int main_file_descriptor, char *buffer)
{
    while(1)
    {
        int read_status = read(main_file_descriptor, buffer, BUFFER_MAIN_READ_SIZE);
        
        if(read_status == -1)
        {
            printf("Main file read faild!!!\n");
            return -1;
        }

        if(!read_status)
            break;

        uint8_t file_name[8];
        uint32_t offset = 0, length = 0;

        get_data(buffer, file_name, &offset, &length);
        printf("file name: %s, offset: %d, length: %d\n", file_name, offset, length);

        if(fork() == 0)
        {
            long long curr_xor = open_file_get_xor(file_name, offset, length);

            if(curr_xor == -1) exit(1);
            
            printf("xor: %d\n", curr_xor);
            
            exit(0);
        } 
    }
}

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Not enough arguments!!!\n");
        exit(1);
    }

    int main_file_descriptor = open(argv[1], O_RDONLY);

    if(main_file_descriptor == -1)
    {
        printf("File can't be open!!!\n");
        exit(2);
    }

    char *buffer = malloc(BUFFER_MAIN_READ_SIZE);

    if(!buffer)
    {
        printf("Can't allocate memory!!!\n");
        exit(3);
    }
    
    read_main_file(main_file_descriptor, buffer);
    
    free(buffer);
    close(main_file_descriptor);

    return 0;
}
