#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

void write_in_file(char b, int fd)
{
    if(write(fd, &b, 1) == -1)
        printf("ERROR WHILE WRITEING!!!\n");
}

void write_number_in_3_base(unsigned int curr, int fd, int depth)
{
    if(!curr && !depth) return;
    write_number_in_3_base(curr / 3, fd, depth - 1);
    write_in_file('0' + curr % 3, fd);

    printf("%u", curr % 3); 
}

void write_all_numbers_in_base_3(unsigned int n, int fd)
{
    for(unsigned int i = 0;i <= n;i++)
    {
        write_number_in_3_base(i, fd, 9);   
        write_in_file('\n', fd);

        printf("\n");
    }
}

int filter_data(char *buffer, int size)
{
    int nums[3];
    nums[0] = nums[1] = nums[2] = 0;

    for(int i = 0;i < size;i++)
        nums[buffer[i] - '0']++;

    return nums[0] == 3 || nums[1] == 4 || nums[2] == 5;
}

void write_in_filter_file(int from, int to)
{
    char buffer[10];
    
    if(lseek(from, 0, SEEK_SET) == -1)
    {
        printf("Lseek faild!!!\n");
        return;
    }

    while(1)
    {
        int read_status = read(from, buffer, 10);

        if(!read_status || read_status < 10) return;
        
        if(read_status == -1)
        {
            printf("Read faild!!!\n");
            return;
        }
        
        if(filter_data(buffer, read_status - 1) && write(to, buffer, read_status) == -1)
            printf("ERROR WHILE WRITEING!!!\n");
    }
}

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        printf("Not enoght arguments!!!\n");
        exit(1);
    }

    int fd = open(argv[1], O_RDWR | O_TRUNC), filter_fd = open(argv[2], O_WRONLY | O_TRUNC);

    if(!fd || !filter_fd)
    {
        printf("File can not be open!!!\n");
        exit(2);
    }

    unsigned int n;
    printf("Enter number: ");
    scanf("%u", &n); 

    write_all_numbers_in_base_3(n, fd);
    write_in_filter_file(fd, filter_fd);
    
    close(fd);
    close(filter_fd);

    return 0;
}
