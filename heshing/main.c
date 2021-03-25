#include<stdlib.h>
#include<string.h>

typedef int value_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
enum bool{ false, true };

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

struct item
{
  struct item *next;
  value_t value;
  char key[];
};

struct hash_table
{
  unsigned n, used;
  struct item **array;
};

int hash(const char *key, int n)
{
    unsigned long long  key_ = 0;
    int len = strlen(key);
    for(int i = 0;i < len;key_ += key[i] << i++);
    return key_ % n;
}

enum bool push(struct item **p, const char *key, value_t value)
{
    struct item *new = malloc(sizeof *new + 1 + strlen(key));
    if (!new) return false;
    strcpy(new->key, key);
    new->value = value;
    new->next = *p;
    *p = new;
    return true;
}

void set_to_zero(struct item **a, unsigned n)
{
    memset(*a, 0, sizeof *a * n);
}

enum bool create(struct hash_table *t, unsigned n)
{
  uint32_t prime_n = find_nearest_prime_above(n);
  t->array = malloc(sizeof *t->array * prime_n);
  t->n = prime_n;
  t->used = 0;
  set_to_zero(&t->array, t->n);
  return !!t->array;
}

enum bool insert(struct hash_table *t, const char *key, value_t value);

enum bool rehash(struct hash_table* t, int size)
{
    struct hash_table new;
    if (!create(&new, size)) return false;
    for (int i = 0; i < t->n; i++)
        if (t->array[i])
            insert(&new, t->array[i]->key, t->array[i]->value);
    free(t->array);
    t->array = new.array;
    t->n = new.n;
    t->used = new.used;
    return true;
}

enum bool insert(struct hash_table *t, const char *key, value_t value)
{
    push(t->array + hash(key, t->n), key, value);
    if (t->n < ++t->used * 2)
        return rehash(t,t->n*2);
    return true;
}

value_t find(struct hash_table *t, const char *key)
{
    for (struct item **p = t->array + hash(key, t->n); *p; p = &(**p).next)
        if (!strcmp((**p).key, key))
            return (*p)->value;
    return 0;
}

value_t remove_(struct hash_table *t, const char *key)
{
  value_t value;
  for (struct item **p = t->array + hash(key, t->n); *p; p = &(**p).next)
    if (!strcmp((**p).key,key))
    {
        value = (*p)->value;
        (*p)->value = 0;
        *p = (**p).next;
        break;
    }
  if (--t->used<t->n / 4)
    rehash(t, t->n / 2);
  return value;
}

void destroy(struct hash_table *t)
{
    free(t->array);
    t->n = 0;
    t->used = 0;
}

struct hash_table table;

int main()
{

  create(&table,10000);
  insert(&table, "hello", 10);
  insert(&table, "hello2", 11);
  insert(&table, "hello1", 12);
  find(&table,"hello");
  remove_(&table, "hello2");
  destroy(&table);

  return 0;
}