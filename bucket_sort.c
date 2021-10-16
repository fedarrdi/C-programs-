/*#include<stdlib.h>
#include <stdio.h>

struct dyn_2d
{
    unsigned element_size, x_dimension, y_dimension;
    char data[];
};

struct dyn_2d *dyn_2d_create(unsigned element_size, unsigned x_dimension, unsigned y_dimension)
{
    struct dyn_2d *arr_data = malloc(sizeof *arr_data + element_size*x_dimension*y_dimension);
    arr_data->element_size = element_size;
    arr_data->x_dimension = x_dimension;
    arr_data->y_dimension = y_dimension;
    return arr_data;
}

void *dyn_2d_access(struct dyn_2d *a, unsigned x, unsigned y)
{
    return a->data + (y*a->x_dimension + x) * a->element_size;
}

void dyn_2d_destroy(struct dyn_2d *a)
{
    free(a);
}

//-------------------- generic code ends here -----------------------

#define TYPE double

int main()
{
    unsigned x_d = 11, y_d = 11;
    struct dyn_2d *a = dyn_2d_create(sizeof(TYPE), x_d, y_d);
    for (int y = 0; y < y_d; y++)
        for (int x = 0; x < x_d; x++)
            *(TYPE *) dyn_2d_access(a, x, y) = x * y;

    for(int y = 0;y < y_d;y++)
        for(int x = 0;x < x_d;x++)
        {
            TYPE *b = dyn_2d_access(a, x, y);
            printf("%f\n", *b);
        }

    dyn_2d_destroy(a);
    return 0;
}*/


#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define SIZE 12

int find_max(int arr[], int n)
{
    int best = -999999999;
    for(int i = 0;i < n;i++)
        if(best < arr[i])
            best = arr[i];
    return best;
}

int cmpfunc (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

void bucket_sort(int arr[], int n)
{
    int max = find_max(arr, n);
    int buckets = 10;
    int divider =  ceil((max + 1) / buckets) + 2;

    int *B = malloc(sizeof((*B)*buckets*divider));
    int *B_i = malloc(sizeof(*B_i)*buckets);

    if(!B || !B_i)
        return;

    for(int i = 0;i < buckets;B_i[i++] = 0);

    for(int i = 0;i < n;i++)
    {
        int j = floor(arr[i] / divider);
        B[j*divider+B_i[j]] = arr[i];
        B_i[j]++;
    }

    for(int i = 0;i < buckets;i++)
        qsort(B + i * divider, B_i[i], sizeof(*B), cmpfunc);

    int index = 0;
    for(int i = 0;i < buckets;i++)
    {
        for(int j = 0;j < B_i[i];j++)
        {
            arr[index++] = B[i*divider+j];
        }
    }
}

int main()
{
    int a[] = {22, 45, 12, 8, 10, 6, 72, 81, 33, 18, 50, 14};
    bucket_sort(a, SIZE);


    return 0;
}
