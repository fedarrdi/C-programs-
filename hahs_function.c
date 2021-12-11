#include<stdio.h>

int len_of_number(unsigned char byte)
{
    int len = 0;
    while(byte)
    {
        byte/=10;
        len++;
    }
    return len;
}

unsigned long long HF(const unsigned char *byte, const size_t number_of_bytes)
{
    unsigned long long HASH = 0;

    for(int i = 0;i < number_of_bytes;i++)
        HASH += ( byte[i] << len_of_number(byte[i]) );

    return HASH;
}

int main()
{

    return 0;
}
