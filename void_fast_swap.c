#include<stdio.h>

struct data 
{
    char a, b, c, d;
    int p, q;
};

int CHARB = sizeof(char),
    INTB = sizeof (int),
    LLB = sizeof (long long);

#define MULTY_TYPE_SWAP(type, a, b)\
    type c = *(type *)a;\
    *(type *)a = *(type *)b;\
    *(type *)b = c

void tues_swap(void *a, void *b, int size)
{
    for(int byte_offset = 0;size;)
    {
        void *p = a + byte_offset, 
             *q = b + byte_offset;

        if(size - LLB >= 0)
        {
            MULTY_TYPE_SWAP(long long, p, q);
            size -= LLB;
            byte_offset += LLB;
            continue;
        }

        if(size - INTB >= 0)
        {
            MULTY_TYPE_SWAP(int, p, q);
            size -= INTB;
            byte_offset += INTB;
            continue;
        }
        
        MULTY_TYPE_SWAP(char, p, q); 
        byte_offset += CHARB;
        size -= CHARB;        
    }
}

int main()
{
    struct data a = {1, 1, 1, 1, 1, 1};
    struct data b = {0, 0, 0, 0, 0, 0};
    printf("%d\n", b.a);
    tues_swap(&a, &b, sizeof a);
    printf("%d\n", b.a);

    int p = 1, q = 2;
    printf("%d %d\n", p, q);
    tues_swap(&p, &q, sizeof p);
    printf("%d %d\n", p, q);
    
    return 0;
}
