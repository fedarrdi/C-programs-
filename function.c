#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

int tues_strlen(const char *str)
{
    const char *end = str;
    for(;*end != '\0'; end++);
    return end - str;
}


void test_tues_strlen()
{
    const char *t1 = "     "; // 5
    const char *t2 = ""; // 0
    const char *t3 = "\n\n\n"; // 3
    const char *t4 = "hello world!!!"; // 14

    if(tues_strlen(t1) == 5)
        printf("Test 1 succes");
    
    if(tues_strlen(t2) == 0)
        printf("Test 2 succes");
    
    if(tues_strlen(t3) == 3)
        printf("Test 3 succes");
    
    if(tues_strlen(t4) == 14)
        printf("Test 4 succes");
}

char *tues_strcat(const char *one, const char *two)
{
    int one_len = tues_strlen(one), 
        two_len = tues_strlen(two), 
        three_len = one_len + two_len;
    
    char *three = malloc(three_len + 1);
    if(!three) return NULL;
    
    int t = 0;
    for(int p = 0;p < one_len;three[t++] = one[p++]);
    for(int q = 0;q < two_len;three[t++] = two[q++]);
    
    return three;
}

void tues_spaw_int(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void tues_swap_char(char *a, char *b)
{
    char c = *a;
    *a = *b;
    *b = c;
}

void tues_swap(void *a, void *b, int size)
{
    for(int i = 0;i < size;i++)
    {
        char *p = a + i,
             *q = b + i;
        tues_swap_char(p, q);
    }
}

char *tues_readline(int fd)
{
    int max_line_size = 256;
    
    char *buff = malloc(max_line_size);
    if(!buff) return NULL;

    int read_status = read(fd, buff, max_line_size);

    if(-1 == read_status)
    {
        printf("Read faild!!!\n");
        free(buff);
        return NULL;
    }

    if(!read_status)
    {
        printf("Unable to read!!!\n");
        free(buff);
        return NULL;
    }

    int new_line_index = -1;
    for(int i = 0;i < read_status;i++)
        if(buff[i] == '\n')
        {
            new_line_index = i;
            break;
        }
    
    char *out = malloc(new_line_index + 1);
    if(!out) return NULL;
    
    for(int i = 0;i < new_line_index;i++)
        out[i] = buff[i];
    
    fd += new_line_index + 1 - max_line_size;

    return out;
}

int main()
{

    char *a = "hello";

    printf("%d\n", tues_strlen(a));
    
    char *p ="aaaa", *q = "bbbb";
    printf("%s\n", tues_strcat(p, q));
    
    int m = 4, n = 9;
    
    printf("m = %d, n = %d\n", m, n);
    tues_swap(&m, &n, 4);
    printf("m = %d, n = %d\n",m, n);

    int fd = open("a.txt", O_RDONLY);
    
    char *buff = malloc(13);
    if(!buff) return 0;
    
    read(fd, buff, 13);
    printf("%s", tues_readline(fd));

    return 0;
}
