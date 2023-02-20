#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

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

void read_file(char *path)
{
    int n = fork();

    if(n == -1)
    {
        printf("Proccess can 't be created!!!\n");
        return;
    }

    if(n == 0)
    {
        printf("%s\n", path);
        exit(0);
    }
}

int iterate_directory(char *path)
{
    DIR *directory = opendir(path);

    if(!directory) 
    {
        printf("Can't open directory!!!\n");
        return 2;
    }
 
    struct dirent *entry;
    while(entry = readdir(directory))
    {   
        char *curr_path = glue_path(path, entry->d_name); 
        if(!curr_path || !strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".")) 
            continue;

        if(entry->d_type == DT_DIR)
        {
            if(iterate_directory(curr_path))
                return 2;
        }

        else
        {
            read_file(curr_path);
        }
    }
    
    return 0;
}

int main(int argc, char **argv)
{

    if(argc < 2)
    {
        printf("Not enough arguments!!!\n");
        exit(1);
    }
    
    exit(iterate_directory(argv[1]));

}
