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
    int HASH = 0;
    for (int i = 0; i < n; i++)
        HASH ^= byte[i];

    return  HASH;
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

struct data_tree * find_data_tree_node()
        

struct hash_tree * find_hash_tree_node(struct hash_tree *hash_tree, int hash)
{
    if(hash_tree->hash_value == hash)
    {

    }

    if(hash < hash_tree->data_tree->value)
        hash_tree->left = find_hash_tree_node(hash_tree, hash);

    if(hash > hash_tree->data_tree->value)
        hash_tree->right = find_hash_tree_node(hash_tree, hash);

    return hash_tree;
}

struct hash_tree * add(struct hash_tree * hash_tree, char *key, int value)
{
    if(!hash_tree)
        return init_hash_tree_node(key, value);

    int hash = hash_func(key, strlen(key));
}

int main()
{
    return 0;
}
