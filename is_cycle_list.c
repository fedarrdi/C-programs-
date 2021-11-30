#include <stdio.h>
#include <stdlib.h>

struct node_t
{
    int value;
    struct node_t* left;
    struct node_t* right;
};

int is_cyclic(struct node_t *node)
{
    for(struct node_t *curr = node->right; ;curr = curr->right)
    {
        if(curr == node)
            return 1;

        if(!curr)
            return 0;
    }
}

struct node_t * add(struct node_t *list, int value)
{
    struct node_t *new_node = malloc(sizeof *new_node), *start = list;
    new_node->right = new_node->left = NULL;
    new_node->value = value;

    if(!list) return new_node;

    for(;list->right;list = list->right);

    list->right = new_node;
    new_node->left = list;

    return start;
}


void make_cycle(struct node_t ** list)
{
    if(!(*list)) return;

    struct node_t *curr= *list;

    for(;curr->right;curr = curr->right);

    curr->right = *list;
    (*list)->left = curr;
}



int main()
{
    struct node_t *list = add(NULL, 1);
    list = add(list, 2);
    list = add(list, 3);
    list = add(list, 4);
    list = add(list, 5);
    list = add(list, 6);
    list = add(list, 7);
    
    int a = is_cyclic(list);

    make_cycle(&list);

    a = is_cyclic(list);

    return 0;
}
