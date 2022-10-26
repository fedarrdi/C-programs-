#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long char_table[255];

void *read_from_file(void *vargp)
{
    printf("hello\n");
    return NULL;
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

    pthread_t tid[2];
    pthread_create(&tid[0], NULL, read_from_file, NULL); 
    pthread_create(&tid[1], NULL, read_from_file, NULL);

    pthread_join(tid[0], NULL);    
    pthread_join(tid[1], NULL);    
   
   return 0;
}
