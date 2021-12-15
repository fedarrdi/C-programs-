#include<stdio.h>
#include<string.h>

struct data_tree
{
    struct data_tree *left, *right;
    char *key;
    int value;
};

struct hash_tree
{
    struct hash_tree * left, *right;
    struct data_tree * data;
    int hash_value;
};

int hash_func(char *byte, size_t n)
{
    int HASH = 0;
    for (int i = 0; i < n; i++)
        HASH ^= byte[i];

    return  HASH;
}

struct hash_tree find_newKey_value

struct hash_tree * add(struct hash_tree * tree, char *key, int data)
{
    int hash = hash_func(key, strlen(key));
    
    if(!tree);//return init_node() hash_tree
        
}

int main()
{
    return 0;
}
