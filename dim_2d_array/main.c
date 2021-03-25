#include<stdlib.h>
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
}
