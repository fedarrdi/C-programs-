#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

#define PROCESS_COUNT 4

#define REDIRECT_STDOUT\
    close(pipes[i][0]);\
    dup2(pipes[i][1], STDOUT_FILENO);\
    close(pipes[i][1]);\

#define REDIRECT_STDIN\
    close(pipes[i - 1][1]); \
    dup2(pipes[i - 1][0], STDIN_FILENO);\
    close(pipes[i - 1][0]);

void close_pipes(int (*pipes)[2])
{
    for(int i = 0;i < PROCESS_COUNT;i++)   
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
}

void execute_command(int command_index, char ***all_args)
{
    if(execvp(all_args[command_index][0], all_args[command_index]) == -1)
    {
        printf("ERROR EXECVP!!!\n");
        return;
    }
}

void create_children(char ***command_list)
{
    int pipes[PROCESS_COUNT][2];
    int pid[PROCESS_COUNT];

    for(int i = 0;i < PROCESS_COUNT; i++)
    {   
        if(pipe(pipes[i]) == -1)
        {
            printf("ERROR CAN'T CREATE A PIPE!!!\n");
            return;
        }
        
        pid[i] = fork();   
        
        if(pid[i] < 0)
        {
            printf("ERROR WHILE CREATING A PROCESS!!!\n");
            return;
        }

        if(pid[i] == 0)
        { 
            
            if(i < PROCESS_COUNT - 1)
            {
                REDIRECT_STDOUT
            }

            if(i > 0)
            {
                REDIRECT_STDIN
            }

            execute_command(i, command_list);

            return;
        }

        else 
        {
            
            if(i != 0)
            {
                close(pipes[i - 1][0]);
                close(pipes[i - 1][1]);
            }
            
            if(i == PROCESS_COUNT - 1)
                for(int j = 0, status = 0;j < PROCESS_COUNT;j++)
                    waitpid(pid[i], &status, 0);
       }
    }

    close_pipes(pipes);
    return;
}

int main(int argc, char **argv)
{
    
    char ***all_args = malloc(PROCESS_COUNT * sizeof(char **));
    
    if(!all_args)
    {
        printf("MALLOC FAILD!!!\n");
        return 0;
    }
    
    char *args1[] = {"cut", "-d", ":", "-f", "7", "/etc/passwd", NULL}; 
    char *args2[] = {"sort", NULL};
    char *args3[] = {"uniq", NULL};
    char *args4[] = {"wc", "-l", NULL};

    all_args[0] = args1;
    all_args[1] = args2;
    all_args[2] = args3;
    all_args[3] = args4;

    create_children(all_args);
    
    free(all_args);
    return 0;
}
