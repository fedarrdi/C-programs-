
#include <stdio.h>
#include <stdlib.h>

#define MIN_INT -214748364
#define MAX_INT 2147483647

struct node_t
{
    int data;
    struct node_t* left;
    struct node_t* right;
};

struct queue_t
{
    struct queue_t *next;
    struct node_t *node;
};

struct node_t * add(struct node_t* tree, int data)
{
    if (!tree)
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

unsigned cnt_elements(struct node_t* tree)
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

struct node_t ** gather_elements(struct node_t *tree, struct node_t **values)
{
    if(!tree) return values;
    values = gather_elements(tree->left, values);
    (*values++) = tree;
    values = gather_elements(tree->right, values);
    return values;
}

struct node_t * recursiv_balance(struct node_t **arr, size_t size)
{
    if(size <= 0) return NULL;

    unsigned index = size / 2;
    struct node_t *tree = arr[index];

    tree->left = recursiv_balance(arr, index);
    tree->right = recursiv_balance(arr + index + 1, size - index - 1);

    return tree;
}

struct node_t *balance_tree(struct node_t *tree)
{
    unsigned element_count = cnt_elements(tree);
    struct node_t** array = malloc(sizeof(struct node_t*) * element_count);
    gather_elements(tree, array);
    return recursiv_balance(array, element_count);
}

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
    if(!queue) return NULL;
    struct queue_t *old_head = queue;
    queue = queue->next;
    free(old_head);
    return queue;
}

void bfs_print(struct node_t * tree)
{

    struct queue_t *queue = queue_push(NULL, tree);
    long long min = tree->data, max = tree->data;
    char has_child_left = 1, has_child_right = 1;
    struct node_t *prev = NULL;

    do
    {
        struct node_t *curr_node = queue->node;
        queue = queue_pop(queue);

        if(curr_node != NULL)
        {
            queue = queue_push(queue, curr_node->left);
            queue = queue_push(queue, curr_node->right);

            if(prev)
                has_child_left = !!prev->left, has_child_right = !!prev->right;
            else
                prev = curr_node;

            if(has_child_left && has_child_right) has_child_right = 0;
            else has_child_left = has_child_right = 1;

            if(curr_node->data < min && has_child_left)
            {
                min = curr_node->data;
                printf("\n");
            }

            if(curr_node->data > max && has_child_right)
            {
                max = curr_node->data;
                printf("\n");
            }

            printf("%d ", curr_node->data);
        }
    }while(queue);

    printf("\n");
    printf("\n");
}



int main()
{
    struct  node_t* tree = add(NULL, 0);
    tree = add(tree, 1);
    tree = add(tree, 2);
    tree = add(tree, 3);
    tree = add(tree, 4);
    tree = add(tree, 5);
    tree = add(tree, 6);
    tree = add(tree, 7);
    tree = add(tree, 8);
    tree = add(tree, 9);
    tree = add(tree, 10);
    tree = add(tree, 11);
    tree = add(tree, 12);

    bfs_print(tree);


    tree = balance_tree(tree);

    bfs_print(tree);

    return 0;
}
