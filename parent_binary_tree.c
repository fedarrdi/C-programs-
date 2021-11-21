#include <stdio.h>
#include <stdlib.h>

struct queue_t
{
    struct queue_t *next;
    struct node_t *node;
};

struct queue_t *queue_push(struct queue_t *queue, struct node_t *node)
{
    struct queue_t *new_node = malloc(sizeof(*new_node));
    new_node->next = NULL;
    new_node->node = node;

    if(!queue)
        return new_node;

    struct queue_t *curr = queue;
    while(curr->next != NULL) curr = curr->next;
    curr->next = new_node;

    return queue;
}

struct queue_t * queue_pop(struct queue_t *queue)
{
    if(!queue)
        return NULL;
    struct queue_t *old_head = queue;
    queue = queue->next;
    free(old_head);
    return queue;
}


struct node_t
{
    struct node_t *left, *right, *parent;
    int data, new_node_num;
};


void bfs_print(struct node_t *tree)
{
    struct queue_t *queue = queue_push(NULL, tree), *buffer = NULL;

    while(queue)
    {
        while(queue)
        {
            struct node_t *curr_node = queue->node;
            printf("%d ", queue->node->data);

            queue = queue_pop(queue);

            if(curr_node->left)
                buffer = queue_push(buffer, curr_node->left);

            if(curr_node->right)
                buffer = queue_push(buffer, curr_node->right);
        }
        printf("\n");
        queue = buffer;
        buffer = NULL;
    }
    printf("\n");
}


int read_path(int number, int *out_bit, int *first_call, int *last_bit_pos)/// if the fucnction is called for the first time first_call = 1
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
    if(!tree->right && !tree->left) return NULL;

    if(!tree->right || tree->left->data > tree->right->data)
    {
        tree->data = tree->left->data;
        tree->left = rearrange(tree->left);
    }

    else if(!tree->left || tree->left->data < tree->right->data)
    {
        tree->data = tree->right->data;
        tree->right = rearrange(tree->right);
    }
    return tree;
}

void print_sorted(struct node_t *tree)
{
    do
    {
        printf("%d  ", tree->data);
        tree = rearrange(tree);
    }while(tree);
    printf("\n");
}


int main()
{


    struct  node_t* tree = add(NULL, 1);
    bfs_print(tree);

    tree = add(tree, 0);
    bfs_print(tree);

    tree = add(tree, 2);
    bfs_print(tree);

    tree = add(tree, 10);
    bfs_print(tree);

    tree = add(tree, 11);
    bfs_print(tree);

    tree = add(tree, 12);
    bfs_print(tree);

    tree = add(tree, 3);
    bfs_print(tree);

    tree = add(tree, 4);
    bfs_print(tree);

    tree = add(tree, 8);
    bfs_print(tree);

    tree = add(tree, 7);
    bfs_print(tree);

    tree = add(tree, 9);
    bfs_print(tree);

    tree = add(tree, 13);
    bfs_print(tree);

    tree = add(tree, 14);
    bfs_print(tree);

    tree = add(tree, 5);
    bfs_print(tree);

    tree = add(tree, 6);
    bfs_print(tree);

    print_sorted(tree);
    return 0;
}
