void put_digits(unsigned long long *arr, struct board board)
{
    int idx = 0,i = 0;
    for(int y = 0;y < board.n;y++)
        for(int x = 0;x < board.m;x++)
        {
            int curr_v = board.data[y][x], n = number_of_bits_in(curr_v);
            for(int j = 0;j < n;j++)
            {
                char curr_bit = ((curr_v & (1 << j)) >> j);
                arr[idx] |= curr_bit << i;
                if(++i > sizeof (unsigned long long ) * 8) idx ++, i = 0;
            }

        }
}


=========================================================================================
    това е целият код за тази част
    
    int number_of_bits_in(int n)
{
    long long p = 1, out = 0;
    while(n >= p)
        p <<= 1, out++;
    return out;
}

unsigned long long number_of_bits_board(const struct board board)
{
    unsigned long long out = 0;
    for(int y = 0;y < board.n;y++)
        for (int x = 0; x < board.m; x++)
               out += number_of_bits_in(board.data[y][x]);
    return out;
}

void put_digits(unsigned long long *arr, struct board board)
{
    int idx = 0,i = 0;
    for(int y = 0;y < board.n;y++)
        for(int x = 0;x < board.m;x++)
        {
            int curr_v = board.data[y][x], n = number_of_bits_in(curr_v);
            for(int j = 0;j < n;j++)
            {
                char curr_bit = ((curr_v & (1 << j)) >> j);
                arr[idx] |= curr_bit << i;
                if(++i > sizeof (unsigned long long ) * 8) idx ++, i = 0;
            }

        }
}

unsigned long long *from_board_to_ind(const struct board board, struct node *node)
{
    int bits = number_of_bits_board(board);
    node->ull_count =  bits / (sizeof(unsigned long long) * 8) + 1;
    unsigned long long *ind = malloc(sizeof *ind * node->ull_count);
    put_digits(ind, board);
    return ind;
}
