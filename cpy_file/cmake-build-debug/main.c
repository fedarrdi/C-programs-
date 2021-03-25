#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define READ_BLOCK 1000000

void* getFileData(FILE *f, unsigned length)
{
    void *buffer = malloc(length);
    if(!buffer) return 0;
    fread(buffer, 1, length, f);
    return buffer;
}

unsigned getFileLength(FILE *f)
{
    fseek(f, 0,SEEK_END);
    unsigned length = ftell(f);
    rewind(f);
    return length;
}

void cpyFileToFile(FILE *r, FILE *w,unsigned r_length)
{
    unsigned length = (r_length/READ_BLOCK + 1);
    unsigned read_block = READ_BLOCK;
    for(int i = 0;i < length;i++)
    {
        if(READ_BLOCK > r_length - i*READ_BLOCK)
            read_block = (r_length - i*READ_BLOCK <= 0) ? (r_length) : (r_length - i*READ_BLOCK);

        void *buffer = getFileData(r, read_block);
        fwrite(buffer, 1, read_block, w);
        fseek(r, (i + 1)*read_block, 0);
        fseek(w, (i + 1)*read_block, 0);
    }   
}

int main(int argc, char** argv)
{
    if (argc < 3) return 0;

    FILE *r = fopen(argv[1], "rb");
    FILE *w = fopen(argv[2],"w+b");

    if(!r || !w) return 0;

    unsigned r_length = getFileLength(r);
    cpyFileToFile(r, w, r_length);

    fclose(r);
    fclose(w);
    return 0;
}
