#include "structs.h"
#include<stdlib.h>

unsigned length(int n)
{
    unsigned l = 0;
    for(;n;n %= 10, l++);
    return l;
}

unsigned findDigits(int n)
{
    if (n == 1) return 1;
    return length(n) + findDigits(n - 1);
}

int number_of_bits_in(int n)
{
    long long p = 1, out = 0;
    while(n < p)
        p <<= 1, out++;
    return out;
}

void put_digits(unsigned long long *arr, struct board board)
{
    int idx = 0,i = 0;
    for(int y = 0;y < board.m;y++)
        for(int x = 0;x < board.n;x++)
        {
            int curr_v = board.data[y][x];
            for(int j = 0;j < number_of_bits_in(curr_v);j++, i++)
            {
                arr[idx] |= curr_v & 1 << i;
                if(i == sizeof (unsigned long long ) * 8) idx ++, i = 0;
            }
        }
}

unsigned long long *from_board_to_ind(const struct board board)
{
    unsigned num_of_ll = findDigits(board.m * board.n - 1) / sizeof(unsigned long long);
    unsigned long long *ind = malloc(sizeof(num_of_ll));
    put_digits(ind, board);
    return ind;
}

float from_board_to_ready_v(struct board board)
{
    int times = 0;
    for(int y = 0;y < board.n;y++)
        for(int x = 0;x < board.m;x++)
            times += (y * board.m + x == board.data[y][x] - 1);

    return (float)times / (float)(board.n * board.m);
}

struct node * init_node(const struct board board)
{
    struct node * new_node = malloc(sizeof *new_node);
    new_node->ready_v = from_board_to_ready_v(board);
    new_node->index = from_board_to_ind(board);
    new_node->ull_count = number_of_bits_in(board.n * board.m) / 8 / sizeof (unsigned long long);
    return new_node;
}

struct board * init_board(int n, int m)
{
    struct board *new_board = malloc(sizeof *new_board);
    new_board->n = n;
    new_board->m = m;
    ///new_board->empty == namirame tova ot faela
    new_board->data = malloc(n * sizeof (**new_board->data));
    for(int i = 0;i < n;i++)
        (*new_board->data) = malloc(m * sizeof (**new_board->data));
    return  new_board;
}