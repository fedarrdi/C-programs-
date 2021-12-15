#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data_tree
{
    struct data_tree *left, *right;
    char *key;
    int value;
};

struct hash_tree
{
    struct hash_tree * left, *right;
    struct data_tree * data_tree;
    int hash_value;
};

int hash_func(char *byte, size_t n)
{
   return 1;
}

struct data_tree *init_data_tree_node(char *key, int value)
{
    struct data_tree * dataTree = malloc(sizeof  *dataTree);
    dataTree->left = dataTree->right = NULL;
    dataTree->key = key;
    dataTree->value = value;
    return dataTree;
}

struct hash_tree *init_hash_tree_node(char *key, int value)
{
    struct hash_tree *new_node = malloc(sizeof *new_node);
    new_node->left = new_node->right = NULL;
    new_node->hash_value = hash_func(key, strlen(key));
    new_node->data_tree = init_data_tree_node(key, value);
    return new_node;
}

struct data_tree * find_data_tree_node(struct data_tree * data_tree, char *key, int value)
{
    if(!data_tree)
        return init_data_tree_node(key, value);

    if(strcmp(data_tree->key, key) < 0)
        data_tree->left = find_data_tree_node(data_tree->left, key, value);

    if(strcmp(data_tree->key, key) > 0)
        data_tree->right = find_data_tree_node(data_tree->right, key, value);

    return data_tree;
}


struct hash_tree * find_hash_tree_node(struct hash_tree *hash_tree, char *key, int value, int hash)
{
    if(!hash_tree)
        return init_hash_tree_node(key, value);

    if(hash_tree->hash_value == hash)
    {
        hash_tree->data_tree = find_data_tree_node(hash_tree->data_tree, key, value);
        return hash_tree;
    }

    if(hash < hash_tree->data_tree->value)
        hash_tree->left = find_hash_tree_node(hash_tree->left, key, value, hash);

    if(hash > hash_tree->data_tree->value)
        hash_tree->right = find_hash_tree_node(hash_tree->right, key, value, hash);

    return hash_tree;
}

struct hash_tree * add(struct hash_tree * hash_tree, char *key, int value)
{
    if(!hash_tree)
        return init_hash_tree_node(key, value);

    int hash = hash_func(key, strlen(key));

    hash_tree = find_hash_tree_node(hash_tree, key, value, hash);

    return hash_tree;
}

int main()
{
    struct hash_tree *hash_tree = add(NULL, "radi", 1);
    hash_tree = add(hash_tree, "radir", 22);
    hash_tree = add(hash_tree, "rar", 4);
    hash_tree = add(hash_tree, "rad", 6);
    hash_tree = add(hash_tree, "rear", 89);

    return 0;
}
