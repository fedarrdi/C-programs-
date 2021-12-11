#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void input_data(unsigned *arr, size_t size)
{
    for(int i = 0;i < size;i++)
    {
        scanf("%d", &arr[i]);
        printf("%d ", arr[i]);
    }
    printf("\nend of input\n");
}

unsigned * find_element(int m, unsigned *arr, size_t size, size_t *out_size)
{
    unsigned  *dim_arr = malloc(sizeof *dim_arr * size);

    for(int i = 0;i < size;i++)
    {
        dim_arr[i] = i != 0 ? dim_arr[i - 1] + arr[i] : arr[i];
    }

    for(int i = 0;i < size;i++)
    {
        if(arr[i] > m && (i == 0 || arr[i] < dim_arr[i - 1]))
        {
            ++*out_size;
            printf("%d ", arr[i]);
        }
    }

    unsigned *out_arr = malloc(size);
    if(!out_arr)
    {
        printf("malloc failed!!!!\n\n\n");
        return NULL;
    }

    int index = 0;
    for(int i = 0;i < size;i++)
    {
        if(arr[i] > m && (i == 0 || arr[i] < dim_arr[i - 1]))
        {
            out_arr[index++] = arr[i];
        }
    }

    free(dim_arr);
    printf("\nend of find\n");

    return out_arr;
}

void print_arr(unsigned *arr , size_t size)
{
    printf("\n size of the arr = %d \n", size);
    for(int i = 0;i < size;i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    printf("Da se otpechati programa za obrabotka na masivite M1[10], M2[15], M3[20] sustaveni ot celi chisla sus stoinosti v intervala [0;999].\n"
           "\nThe name of the author\n");

    unsigned M1[10], M2[15], M3[20];

    input_data(M1, 10);
    input_data(M2, 15);
    input_data(M3, 20);

    print_arr(M1, 10);
    print_arr(M2, 15);
    print_arr(M3, 20);

    size_t M1_size = 0, M2_size = 0, M3_size = 0;
    unsigned *M1_out = find_element(17, M1, 10, &M1_size);
    unsigned *M2_out = find_element(12, M2, 15, &M2_size);
    unsigned *M3_out = find_element(14, M3, 20, &M3_size);

    print_arr(M1_out, M1_size);
    print_arr(M2_out, M2_size);
    print_arr(M3_out, M3_size);

    return 0;
}
