#include <stdio.h>
#include <stdlib.h>

int MAX(int a, int b) { return a > b ? a : b; }
int ABS(int a) { return  a > 0 ? a : -a; }

struct node_t
{
    int height, balance, data;
    struct node_t *left, *right, *parent;
};


struct node_t *init_node(int data)
{
    struct node_t *new_node = malloc(sizeof *new_node);
    new_node->left = new_node->right =  new_node->parent = NULL;
    new_node->height = new_node->balance = 0;
    new_node->data = data;
    return new_node;
}

struct node_t *find_newNode_place(struct node_t *parent, struct node_t *tree, struct node_t *new_node)
{
    if(!tree)
    {
        new_node->parent = parent;
        return new_node;
    }

    if(new_node->data < tree->data)
        tree->left = find_newNode_place(tree, tree->left, new_node);

    if(new_node->data > tree->data)
        tree->right = find_newNode_place(tree, tree->right, new_node);

    return tree;
}

struct node_t * input_add(struct node_t *tree, int data)
{
    struct node_t *new_node = init_node(data);

    if(!tree) return new_node;

    tree = find_newNode_place(NULL, tree, new_node);

    return tree;
}

int calc_heights(struct node_t **tree)
{
    if((!*tree)) return -1;

    (*tree)->height = MAX(calc_heights(&(*tree)->left), calc_heights(&(*tree)->right)) + 1;

    return  (*tree)->height;
}

void calc_balance(struct node_t **tree)
{
    if(!(*tree)) return;

    if(!(*tree)->right && !(*tree)->left)
        (*tree)->balance = 0;

    else if(!(*tree)->right)
        (*tree)->balance = (*tree)->height;

    else if(!(*tree)->left)
        (*tree)->balance = -(*tree)->height;
    else
        (*tree)->balance = (*tree)->left->height - (*tree)->right->height;

    calc_balance(&(*tree)->left);
    calc_balance(&(*tree)->right);
}

struct node_t* rotate_left(struct node_t* tree)
{
    puts("rotate left");
    struct node_t *temp = tree->right;

    temp->parent = tree->parent;
    tree->parent = temp;
    tree->right = temp->left;
    temp->left = tree;

    return temp;
}

struct node_t* rotate_right(struct node_t* tree)
{
    puts("rotate right");
    struct node_t *temp = tree->left;

    temp->parent = tree->parent;
    tree->parent = temp;
    tree->left = temp->right;
    temp->right = tree;

    return temp;
}

struct node_t * broken_rotate_left(struct node_t *branch)
{
    puts("rotate broken left");
    struct node_t * C = branch->right->left, *B = branch->right;
    B->left = C->right;
    if(B->left) B->left->parent = B;
    B->parent = C;
    C->parent = branch;
    C->right = B;
    branch->right = C;
    return  rotate_left(branch);
}

struct node_t * broken_rotate_right(struct node_t *branch)
{
    puts("rotate broken right");
    struct node_t * C = branch->left->right, *B = branch->left;
    branch->left = C;
    B->parent = C;
    C->parent = branch;
    B->right = C->left;
    if(C->left)C->left->parent = C;
    C->left = B;
    return rotate_right(branch);
}

struct node_t * balance(struct node_t *node)
{
    struct node_t *tmp;
    while(node)
    {
        calc_heights(&node);
        calc_balance(&node);
        if (ABS(node->balance) >= 2)
        {
            if (node->balance < 0)
            {
                if (node->right->balance < 0)
                    node = rotate_left(node);
                else
                    node = broken_rotate_left(node);

            }
            else
            {
                if (node->left->balance > 0)
                    node = rotate_right(node);
                else
                    node = broken_rotate_right(node);
            }
        }

        tmp = node;

        if(node->parent)
        {
            if (node->data > node->parent->data)
                node->parent->right = node;
            else
                node->parent->left = node;
        }

        node = node->parent;
    }

    return tmp;
}


struct node_t * AVL_add(struct node_t * tree, int data)
{
    struct node_t *new_node = init_node(data);

    if(!tree) return new_node;

    tree = find_newNode_place(NULL, tree, new_node);

    calc_heights(&tree);
    calc_balance(&tree);

    tree = balance(new_node);

    return tree;
}

void print_tree(struct  node_t *tree)
{
    if(!tree) return;
    printf("%d (height = %d, balance = %d)   \n", tree->data, tree->height, tree->balance);
    print_tree(tree->left);
    print_tree(tree->right);
}

void iterate_over_tree(struct node_t *tree, struct node_t **result1, struct node_t **result2, int *cnt)
{
    if(!tree) return;

    iterate_over_tree(tree->left, result1,  result2, cnt);

    if (!(*cnt))
        *result1 = AVL_add(*result1, tree->data);
    else
        *result2 = AVL_add(*result2, tree->data);

    *cnt = !(*cnt);

    iterate_over_tree(tree->right, result1,  result2, cnt);
}


void split(struct node_t *tree, struct node_t *result1, struct node_t *result2)
{
    int cnt = 0;
    iterate_over_tree(tree, &result1, &result2, &cnt);

    printf("tree1 \n");
    print_tree(result1);
    printf("\n tree2 \n");
    print_tree(result2);
}



int main()
{
    struct node_t *input_tree = input_add(NULL, 10);
    input_tree = input_add(input_tree, 5);
    input_tree = input_add(input_tree, 3);
    input_tree = input_add(input_tree, 6);
    input_tree = input_add(input_tree, 8);
    input_tree = input_add(input_tree, 15);
    input_tree = input_add(input_tree, 12);
    input_tree = input_add(input_tree, 18);
    input_tree = input_add(input_tree, 13);

    struct node_t *tree1 = NULL, *tree2 = NULL;

    split(input_tree, tree1, tree2);

    return 0;
}



