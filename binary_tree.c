#include <stdio.h>
#include <stdlib.h>

struct node_t
{
    int data;
    struct node_t* left;
    struct node_t* right;
};

struct node_t* add(struct node_t* tree, int data)
{
    if (tree == NULL)
    {
        struct node_t* new_node = malloc(sizeof(struct node_t));
        new_node->data = data;
        new_node->left = new_node->right = NULL;
        return new_node;
    }

    if (data < tree->data)
        tree->left = add(tree->left, data);

    if (data > tree->data)
        tree->right = add(tree->right, data);


    return tree;
}

int cnt_elements(struct node_t* tree)
{
    if (tree == NULL) return 0;
    return cnt_elements(tree->left) + cnt_elements(tree->right)+1;
}

int search(struct node_t* tree,int data)
{
    if (tree == NULL)
        return 0;

    if (data == tree->data)
        return 1;

    if (data < tree->data)
        return search(tree->left, data);

    else
        return search(tree->right, data);
}

void print_tree(struct node_t* tree)
{
    if (tree == NULL) return;

    printf("%d\n", tree->data);

    print_tree(tree->left);
    print_tree(tree->right);

}

struct node_t * re_arrange(struct node_t *branch, struct node_t *tree)
{

    if (tree == NULL)
        return branch;

    if (branch->data < tree->data)
         tree->left = re_arrange(branch, tree->left);

    else
         tree->right = re_arrange(branch, tree->right);

    return tree;
}


struct node_t * remove_(struct node_t *tree, int data)
{
    if(!tree) return NULL;

    if(data < tree->data)
        tree->left = remove_(tree->left, data);

    if(data > tree->data)
        tree->right = remove_(tree->right, data);

    if(data == tree->data)
    {
            if(!tree->left && !tree->right)
            {
                free(tree);
                tree = NULL;
            }
            else if(tree->left && tree->right)
            {
                struct node_t * right_child = tree->right, *left_child = tree->left;
                free(tree);
                tree = right_child;
                tree = re_arrange(left_child, right_child);
            }

            else if(tree->left || tree->right)
            {
                struct node_t *tmp = tree->left ? tree->left : tree->right;
                free(tree);
                tree = tmp;
            }
    }

    return tree;
}

int main()
{
    struct  node_t* tree = add(NULL, 13);
    tree = add(tree, 13);
    tree = add(tree, 8);
    tree = add(tree, 5);
    tree = add(tree, 3);
    tree = add(tree, 2);
    tree = add(tree, 1);
    tree = add(tree, 4);
    tree = add(tree, 9);
    tree = add(tree, 6);
    tree = add(tree, 7);
    tree = add(tree, 11);
    tree = add(tree, 10);
    tree = add(tree, 12);


    tree = remove_(tree, 8);

    print_tree(tree);
    return 0;
}
