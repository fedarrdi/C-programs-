#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define SIZE 13

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

    int *B = malloc(sizeof(*B)*buckets*divider);
    int *B_i = malloc(sizeof(*B_i)*buckets);

    if(!B || !B_i) return;

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
        for(int j = 0;j < B_i[i];j++)
            printf("%d ", B[i*divider+j]);
    free(B);
    free(B_i);
}

int main()
{
    int a[] = {22, 45, 12, 8, 10, 6, 72, 81, 33, 18, 50, 14, 81};
    bucket_sort(a, SIZE);
    return 0;
}
