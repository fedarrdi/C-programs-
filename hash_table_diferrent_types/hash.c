#define _CRT_SECURE_NO_WARNINGS
#include "hash.h"
uint32_t sqrt64(uint64_t r)
{
    uint64_t t, b, c = 0;
    for (b = 1ull << 62; b; b >>= 2)
    {
        t = c + b;
        c >>= 1;
        if (t <= r)
        {
            r -= t;
            c += b;
        }
    }
    return (uint32_t)c;
}
int find_nearest_prime_above(unsigned n)
{
    for(uint64_t c_r = n;;c_r++)
    {
        enum bool a = true;
        if(c_r % 6 == 1 || c_r % 6 == 5)
        {
            uint32_t n1 = sqrt64(c_r);
            for (int i = 2; i < n1; i++)
                if (!(c_r % i))
                {
                    a = false;
                    break;
                }
            if (a) return c_r;
        }
    }
}
void set_to_zero(struct hash_item **a, unsigned n)
{
    memset(*a, 0, sizeof *a * n);
}
enum bool hash_create(struct hash_table *t, unsigned n, hash_compare_t compare, hash_calc_t hash, hash_key_of_t key_of)
{
    unsigned n1 = find_nearest_prime_above(n);
    t->array = malloc(sizeof *t->array*n1);
    if(!t->array) return false;
    t->n = n1;
    t->used = 0;
    t->key_of = key_of;
    t->calc = hash;
    t->compare = compare;
    set_to_zero(&t->array, t->n);
    return true;
}
enum bool rehash(struct hash_table* t, unsigned size)
{
    struct hash_table new;
    if (!hash_create(&new, size, t->compare, t->calc, t->key_of)) return false;
    for (int i = 0; i < t->n; i++)
        if (t->array[i])
            hash_insert(&new, t->array[i]);
    free(t->array);
    t->array = new.array;
    t->n = new.n;
    t->used = new.used;
    return true;
}
void hash_insert(struct hash_table* t, struct hash_item* inserted)
{
    struct hash_item **p=t->array + t->calc(t->key_of(inserted), t->n);
    inserted->next = *p;
    *p = inserted;
    if (t->n < ++t->used * 2)
        rehash(t,t->n*2);
}
struct hash_item *hash_find(struct hash_table *t, void *key)
{
    for (struct hash_item **p = t->array + t->calc(key, t->n); *p; p = &(**p).next)
        if(t->compare(key, t->key_of(*p)))
            return *p;
    return 0;
}
struct hash_item *hash_remove(struct hash_table* t, void *key)
{
    if (--t->used < t->n / 4)
        rehash(t, t->n / 2);

    struct hash_item *r_p = 0;
    for (struct hash_item **p = t->array + t->calc(key, t->n); *p; p = &(**p).next)
        if(t->compare(key, t->key_of(*p)))
        {
            r_p = *p;
            *p = (**p).next;
            break;
        }
    return r_p;
}
void destroy(struct hash_table *t)
{
    t->used = 0;
    t->n = 0;
    free(t->array);
    t->compare = 0;
    t->calc = 0;
    t->key_of = 0;
}