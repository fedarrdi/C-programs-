#include <stdio.h>
#include <stdlib.h>

struct tree_node
{
    struct tree_node *left, *right;
    int value;
};

struct list_node
{
    struct tree_node *v_node;
    struct list_node *next;
};

void add_list(struct list_node **start, struct tree_node *new_node)
{

    if (!(*start))
    {
        *start = malloc(sizeof  **start);
        (*start)->next = NULL;
        (*start)->v_node = new_node;
        return;
    }

    add_list(&(*start)->next, new_node);
}

void clear_list(struct list_node ** start)
{
    for(struct list_node *iterator = *start; iterator;)
    {
        struct list_node *next = iterator->next;
        free(iterator);
        iterator = next;
    }
    (*start) = NULL;
}



void add_tree(struct tree_node **root, int value)
{
    if(!(*root))
    {
        *root = malloc(sizeof **root);
        (*root)->left = (*root)->right = NULL;
        (*root)->value = value;
        return;
    }

    if(value > (*root)->value)
        add_tree(&(*root)->right, value);

    if(value < (*root)->value)
        add_tree(&(*root)->left, value);
}


unsigned find_tree_width(struct tree_node *root)
{
    if(!root) return 0;

    struct list_node *l1 = NULL, *l2 = NULL;

    add_list(&l1, root);

    int best_width = -1, curr_width = 0 ;

    while(l1)
    {
        for(struct list_node *itr = l1; itr ; itr = itr->next)
        {
            if(itr->v_node->left)
            {
                add_list(&l2, itr->v_node->left);
                curr_width ++;
            }

            if(itr->v_node->right)
            {
                add_list(&l2, itr->v_node->right);
                curr_width ++;
            }
        }

        clear_list(&l1);
        l1 = l2;
        l2 = NULL;

        if(best_width < curr_width)
            best_width = curr_width;

        curr_width = 0;
    }
    return best_width;
}

int main()
{
    struct tree_node *binary_tree_root = NULL;
    add_tree(&binary_tree_root, 10);
    add_tree(&binary_tree_root, 5);
    add_tree(&binary_tree_root, 20);
    add_tree(&binary_tree_root, 3);
    add_tree(&binary_tree_root, 6);
    add_tree(&binary_tree_root, 15);
    add_tree(&binary_tree_root, 25);
    printf("%d",  find_tree_width(binary_tree_root));

    return 0;
}
