#include <pthread.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

#define BUFFER_SIZE 10

long long char_table[255];

void *read_from_file(void *file_name_)
{
    char *file_name = (char *) file_name_;

    int fd = open(file_name, O_RDONLY);

    if(fd == -1)
    {
        printf("Unable to open given files!!!\n");
        exit(2);
    }
    
    char *buff = malloc(BUFFER_SIZE * sizeof *buff);

    if(!buff)
    {
        printf("Can't allocate memory!!\n");
        exit(3);
    }
    
    while(1)
    {

        int read_status = read(fd, buff, BUFFER_SIZE);
    
        if(!read_status)
            break;

        if(read_status == -1)
        {
            printf("read faild!!!\n");
            exit(4);
        }

       for(int i = 0;i < read_status;i++)
            printf("%c", buff[i]);
    }

}

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Not enough arguments given!!!\n");
        exit(1);
    }
    
    pthread_t tid[2];
    pthread_create(&tid[0], NULL, read_from_file, (void *) argv[1]); 
    pthread_create(&tid[1], NULL, read_from_file, (void *) argv[1]);

    pthread_join(tid[0], NULL);    
    pthread_join(tid[1], NULL);    
   
   return 0;
}
