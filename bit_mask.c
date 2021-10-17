#include <stdio.h>

///mrejov maska

unsigned long long pow(int base, int power)
{
    unsigned long long out = 1;
    for(int i = 0;i < power;i++)
        out *= base;
    return out;
}

int n_of_bits(unsigned long long number)
{
    int a, b;
    for(int i = 0;i < 32;i++)
    {
        b = pow(2, i);
        a = number - b;
        if(a <= 0) return i;
    }
}

unsigned long long get_net_size(unsigned long long  mask)
{
    unsigned long long biggest_mask = pow(2, 32) - 1;
    unsigned long long number = biggest_mask ^ mask;
    short number_of_bits = n_of_bits(number);
    int n_of_addresses = pow(2, number_of_bits);
    return n_of_addresses - 2;
}

int main()
{
    unsigned long long in = pow(2, 32) - 8;
    unsigned long long a = get_net_size(in);

    return 0;
}
