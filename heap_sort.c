#include <stdio.h>
#include <stdlib.h>

struct node_t
{
    struct node_t *left, *right, *parent;
    int data, new_node_num;
};


int read_path(int number, int *out_bit, int *first_call, int *last_bit_pos)/// if the function is called for the first time first_call = 1
{
    int left_most = 1 << 30;
    for(int i = *last_bit_pos;i <= 30;i++)
    {
        if(!(*first_call))
        {
            *out_bit = !!( (left_most >> i)  & number );
            *last_bit_pos = i + 1;
            return 1;
        }

        if( ( (left_most >> i)  & number)  && *first_call)
            *first_call = 0;
    }

    return 0;///the path has been red no more to read
}

struct node_t *init_node(int data)
{
    struct node_t *new_node = malloc(sizeof(*new_node));
    if(!new_node) return NULL;

    new_node->data = data;
    new_node->left = new_node->right = new_node->parent = NULL;
    new_node->new_node_num = 1;

    return new_node;
}

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

struct node_t * add(struct node_t *tree, int data)
{
    struct node_t *new_node = init_node(data);

    if(!tree) return new_node;

    new_node->new_node_num = ++tree->new_node_num;

    int bit, first_call = 1, bit_pos = 0;
    struct node_t *root = tree, *parent = tree;

    while(read_path(new_node->new_node_num, &bit, &first_call, &bit_pos))
    {
        parent = tree;
        tree = bit ? tree->right : tree->left;
    }

    tree = parent;
    bit ? (tree->right = new_node) : (tree->left = new_node);
    new_node->parent = parent;

    while(new_node->parent && new_node->data > new_node->parent->data)
    {
        swap(&new_node->data, &new_node->parent->data);
        new_node = new_node->parent;
    }

    return root;
}

struct node_t * rearrange(struct node_t *tree)
{
    if(!tree->right && !tree->left)
    {
        free(tree);
        return NULL;
    }

    if(!tree->left)
    {
        tree->data = tree->right->data;
        tree->right = rearrange(tree->right);
    }

    else if(!tree->right)
    {
        tree->data = tree->left->data;
        tree->left = rearrange(tree->left);
    }

    else if(tree->left->data > tree->right->data)
    {
        tree->data = tree->left->data;
        tree->left = rearrange(tree->left);
    }

    else if(tree->left->data < tree->right->data)
    {
        tree->data = tree->right->data;
        tree->right = rearrange(tree->right);
    }

    return tree;
}

void sort(struct node_t *tree, int *array)
{
    unsigned index = 0;
    do
    {
        array[index++] = tree->data;
        tree = rearrange(tree);
    }while(tree);
}


void heapsort(int *array, unsigned int size)
{
    struct node_t *tree = NULL;

    for (int i = 0; i < size; i++)
        tree = add(tree, array[i]);

    sort(tree, array);

    for(int i = 0;i < size;i++)
        printf("%d ", array[i]);
}

int main()
{

    int array[10] = {10, 9 , 8, 7, 6, 5, 4, 3, 2, 1};

    heapsort(array, 10);

    return 0;
}
