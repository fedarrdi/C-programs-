#include <stdio.h>
#include <stdlib.h>

char UpCaseLetter(char letter)
{
    return (letter >= 'a' && letter <= 'z') ? letter - 'a' + 'A' : letter;
}

void UpCaseStr(char *str, int length)
{
    for(int i = 0;i < length;i++)
       str[i] = UpCaseLetter(str[i]);
}

char* getFileText(FILE *f, int length)
{
    char *buffer = malloc(sizeof *buffer*length);
    if(!buffer) return 0;
    fread( buffer , 1, length , f);
    return buffer;
}

int get_length_of_file(FILE *f)
{
    fseek(f, 0,SEEK_END);
    int length = ftell(f);
    rewind(f);
    return length;
}

int main(int argc, char** argv)
{
    if (argc < 2) return 0;

    FILE *f = fopen(argv[1],"r+");
    if(!f) return 0;

    int length = get_length_of_file(f);

    char *buffer = getFileText(f, length);
    UpCaseStr(buffer, length);

    f = fopen(argv[1], "w");
    fwrite(buffer, 1, length, f);
    fclose(f);
    return 0;
}
