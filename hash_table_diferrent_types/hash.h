#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <string.h>
struct hash_item
{
    struct hash_item *next;
};
#define container_of(p,t,m) ( (t *)_container_of( (p), (size_t)&((t *)0)->m ))
typedef int (*hash_compare_t)(const void *l, const void *r);
typedef unsigned (*hash_calc_t)(const void *key, unsigned n);
typedef const void* (*hash_key_of_t)(struct hash_item* item);
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
enum bool { false, true };

struct hash_table
{
    unsigned n, used;
    struct hash_item **array;
    hash_compare_t compare;
    hash_calc_t calc;
    hash_key_of_t key_of;
};

uint32_t sqrt64(uint64_t r);
int find_nearest_prime_above(unsigned n);
void set_to_zero(struct hash_item **a, unsigned n);
enum bool hash_create(struct hash_table *t, unsigned n, hash_compare_t compare, hash_calc_t hash, hash_key_of_t key_of);
enum bool rehash(struct hash_table* t, unsigned size);
void hash_insert(struct hash_table* t, struct hash_item* inserted);
struct hash_item *hash_find(struct hash_table *t, void *key);
struct hash_item *hash_remove(struct hash_table* t, void *key);
void destroy(struct hash_table *t);
static inline void *_container_of(void *p, size_t offset) { return p ? (char *)p - offset : 0; }