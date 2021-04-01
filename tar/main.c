#include<stdlib.h>
#include<string.h>
#include<stdio.h>

struct tar_header
{
    char name[100];
    unsigned size;
};

enum bool{false, true};

#define BLOCK_SIZE 4096

char* format_name(const char *full_path)
{
    int last_seen = -1, size = strlen(full_path);
    for(int i = 0;i < size;i++)
        if(full_path[i] == '/')
            last_seen = i;
    return full_path + (last_seen + 1);
}

unsigned get_file_length(FILE *f)
{
    fseek(f, 0,SEEK_END);
    unsigned length = ftell(f);
    rewind(f);
    return length;
}

enum bool copy_file(FILE *src, FILE *dest)
{
    size_t size;
    void *buffer = malloc(BLOCK_SIZE);
    if(!buffer) return false;
    do
    {
        size = fread(buffer, 1, BLOCK_SIZE, src);
        fwrite(buffer, 1, size, dest);
    }while (size == BLOCK_SIZE);
    free(buffer);
    return true;
}

enum bool copy_header(const char *file_name, FILE *from, FILE *to)
{
    struct tar_header header;
    strcpy(header.name, file_name);
    header.size = get_file_length(from);
    fwrite(&header, sizeof(header), 1, to);
    return true;
}

enum bool tar_add(const char *file_name, const char *directory_name)
{
    FILE *from = fopen(file_name, "r+b"), *to = fopen(directory_name, "r+b");
    if(!from || !to) return false;
    fseek(to, 0,SEEK_END);
    if(!copy_header(format_name(file_name), from, to) || !copy_file(from, to)) return false;
    return true;
}

enum bool tar_extract(const char *file_name, const char *directory_name)
{
    FILE *f = fopen(directory_name, "r+b");
    if(!f) return false;
    struct tar_header header;
    unsigned offset = 0, dir_size = get_file_length(f);
    while(dir_size > offset)
    {
        fread(&header, 1, 104, f);
        if (!strcmp(header.name, file_name))
        {
            void *buffer = malloc(header.size);
            if (!buffer) return false;
            fread(buffer, 1, header.size, f);
            FILE *new = fopen(file_name, "wb");
            if (!new) return false;
            fwrite(buffer, 1, header.size, new);
            return true;
        }
        offset += header.size + 104;
        fseek(f,offset, 0);
    }
    return false;
}

enum bool tar_remove(const char *file_name, const char *directory_name)
{
    FILE *f = fopen(directory_name, "r+b");
    if(!f) return false;
    struct tar_header header;
    unsigned offset = 0, dir_size = get_file_length(f);
    while(dir_size > offset)
    {
        fread(&header, 1, 104, f);
        if (!strcmp(header.name, file_name))
        {
            void *buffer_r = malloc(dir_size), *buffer_w= malloc(dir_size - 104 - header.size);
            if(!buffer_r || !buffer_w) return false;
            rewind(f);
            fread(buffer_r, 1 , dir_size, f);

            for(int i = 0, j = 0;i < dir_size;i++)
                if(i < offset || i > offset + 103 + header.size)
                    ((char *) buffer_w)[j++] = ((char *) buffer_r)[i];

            FILE *f = fopen(directory_name, "wb");
            if(!f) return false;
            fwrite(buffer_w,1,  dir_size - 104 - header.size, f);
            return true;
        }
        offset += header.size + 104;
        fseek(f,offset, 0);
    }
    return false;
}

enum bool get_operations(const char *opr, const char *file_name, const char *directory_name)
{
    if(!strcmp(opr, "add") && tar_add(file_name, directory_name)) return true;
    if(!strcmp(opr, "extract") && tar_extract(file_name, directory_name)) return true;
    if(!strcmp(opr, "remove") && tar_remove(file_name, directory_name)) return true;
    return false;
}

int main(int argc, char** argv)
{
    if(argc < 4) return 0;

    if(!get_operations(argv[1], argv[2], argv[3]))
        printf("Operation did not go as planet try again!!!\n");

    return 0;
}

