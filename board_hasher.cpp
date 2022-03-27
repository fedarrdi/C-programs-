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
