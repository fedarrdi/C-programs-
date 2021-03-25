#include"hash.h"
#include<malloc.h>
#include<string.h>

#define container_of(p,t,m) ( (t *)_container_of( (p), (size_t)&((t *)0)->m ))

struct hash_table table;

struct our_item
{
    struct hash_item hash;
    int value;
    char key[];
};

static int cmp_str(const void *l, const void *r)
{
    return !strcmp(l, r);
}

static unsigned calc_str(const void *key, unsigned n)
{
    unsigned long long key_ = 0, i = 0;
    for(unsigned const char *s = key;*s;s++, i++)
        key_ += *s << i;
    return key_%n;
}

static const void *key_of_str(struct hash_item *item)
{
    return container_of(item, struct our_item, hash)->key;
}

void main()
{
    hash_create(&table,1000,cmp_str,calc_str,key_of_str);

    struct our_item *p = malloc(sizeof * p + sizeof"one");
    if (!p) return;
    p->value = 1;
    strcpy(p->key, "one");
    hash_insert(&table, &p->hash);

    p = malloc(sizeof * p + sizeof"two");
    if (!p) return;
    p->value = 2;
    strcpy(p->key, "two");
    hash_insert(&table, &p->hash);

    struct hash_item *a = hash_find(&table, "one");
    p = container_of(a, struct our_item, hash);

    a = hash_remove(&table, "one");
    free(container_of(a, struct our_item, hash));

    a = hash_remove(&table, "two");
    p = container_of(a, struct our_item, hash);

    a = hash_remove(&table, "two");
    free(container_of(a, struct our_item, hash));

    destroy(&table);
}