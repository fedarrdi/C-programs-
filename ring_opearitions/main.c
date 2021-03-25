#include <string.h>
#include <stdio.h>
#include <malloc.h>

struct item
{
    struct item *next;
    int data;
    char key[1];
};

void ring_add(struct item **ring, const char *key, int data)
{
    struct item *new = malloc(sizeof *new+strlen(key));
    strcpy(new->key, key);
    new->data = data;
    if(!*ring) new->next = new;
    else new->next = (*ring)->next, (*ring)->next = new;
    *ring = new;
}
enum bool {false, true};

void ring_merge(struct item *a, struct item *b)
{
    struct item *c = a->next;
    a->next = b->next;
    b->next = c;
}

void ring_split(struct item *a, struct item *b)
{
    struct item *c = a->next;
    a->next = b->next;
    b->next = c;
}

int ring_find_and_remove(struct item *ring, const char *s)
{
    struct item *curr_item = ring->next, *last_item = ring;
    while(strcmp(curr_item->key, s))
        last_item = curr_item, curr_item = curr_item->next;
    last_item->next = curr_item->next;
    int data = curr_item->data;
    free(curr_item);
    return data;
}


int main()
{
    struct item *ring1 = 0, *ring2=0;

    ring_add(&ring1, "first",1);
    ring_add(&ring1, "second",2);

    ring_add(&ring2, "third", 3);
    ring_add(&ring2, "forth", 4);
    ring_add(&ring2, "fifth", 5);
    ring_add(&ring2, "sixth", 6);

    ring_merge(ring1, ring2);


    ring_find_and_remove(ring1, "forth");
    ring_find_and_remove(ring2, "first");

    return 0;
}