#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

char *create_mv_file_path(char *move_path, char *file_path)
{
    char *full_path = malloc(strlen(move_path) + strlen(file_path) + 1);
    if(!full_path)
        return 0;

    sprintf(full_path, "%s%s\0", move_path, file_path);
    
    for(int i = strlen(move_path) + 1; i < strlen(full_path); i++)
        if(full_path[i] == '/')
            full_path[i] = '|';
    
    return full_path;
}

int move_file(char *move_path, char *file_path)
{
    char *path = create_mv_file_path(move_path, file_path);
    int new_file = open(path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR); 
    if(new_file == -1)
    {
        printf("Can't create file!!!\n");
        free(path);
        return 0;
    }

    int file = open(file_path, O_RDONLY);
    if(file == -1)
    {
        printf("Can't open file!!!\n");
        free(path);
        close(new_file);
        return 0;
    }
    
    char buffer[100];
    
    while(1)
    {
        int read_status = read(file, buffer, 100);
        if(read_status == -1 || !read_status)
            break;

        int write_status = write(new_file, buffer, read_status);
        if(write_status == -1)
            break;
    }

    free(path);
    close(new_file);
    close(file);
    return 1;
}


char *glue_path(char *curr_path, char *next_dir)
{
    char *full_path = malloc(strlen(curr_path) + strlen(next_dir) + 2);
    if(!full_path)
    {
        printf("Can't allocate memory!!!\n");
        return 0;
    }

    sprintf(full_path, "%s/%s\0", curr_path, next_dir);
    return full_path;
}


void iterate_directory(char *path, char *move_path)
{
    DIR *directory = opendir(path);

    if(!directory) 
    {
        printf("Can't open directory!!!\n");
        return;
    }
 
    struct dirent *entry;
    while(entry = readdir(directory))
    {       

        if(!strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".")) 
            continue;

        char *curr_path = glue_path(path, entry->d_name); 
        if(!curr_path)
            return;

        if(entry->d_type == DT_DIR)
            iterate_directory(curr_path, move_path);

        else
        {
            printf("file: %s\n", entry->d_name);
            move_file(move_path, curr_path);
        }

        free(curr_path);
    }

    closedir(directory);
}

void delete_directory(char *path)
{
    DIR *directory = opendir(path);

    if(!directory) 
    {
        printf("Can't open directory!!!\n");
        return;
    }
 
    struct dirent *entry;
    while(entry = readdir(directory))
    {       

        if(!strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".")) 
            continue;

        char *curr_path = glue_path(path, entry->d_name); 
        if(!curr_path)
            return;

        if(entry->d_type == DT_DIR)
        {
            delete_directory(curr_path);
            
            if(rmdir(curr_path) == -1) 
                printf("Can't removed directory: %s\n", curr_path);

            else 
                printf("Removed directory: %s\n", curr_path);
        }

        else if (!unlink(curr_path))
            printf("Removed file: %s\n", curr_path);
        else
            printf("Can`t remove file: %s\n", curr_path);
        
        free(curr_path);
    }

    closedir(directory);
}

void remove_directories(char *path)
{
    DIR *directory = opendir(path);

    if(!directory) 
    {
        printf("Can't open directory!!!\n");
        return;
    }
 
    struct dirent *entry;
    while(entry = readdir(directory))
    {       

        if(!strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".")) 
            continue;

        char *curr_path = glue_path(path, entry->d_name); 
        if(!curr_path)
            return;

        if(entry->d_type == DT_DIR)
        {
            delete_directory(curr_path);
            
            if(rmdir(curr_path) == -1) 
                printf("Can't removed directory: %s\n", curr_path);

            else 
                printf("Removed directory: %s\n", curr_path);
        }

        free(curr_path);
    }

    closedir(directory);
}

int main(int argc, char **argv)
{

    if(argc < 2)
    {
        printf("Not enough arguments!!!\n");
        exit(1);
    }
    
    iterate_directory(argv[1], argv[1]);
    remove_directories(argv[1]);
    
    exit(0);
}
