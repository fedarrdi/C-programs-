#include <string.h>
#include <stdio.h>
#include <malloc.h>

struct queue
{
    struct item *head, *tail;
};

struct item
{
    struct item *next;
    char name[1];
};

enum bool { false, true } ;

enum bool enqueue(struct queue *q, const char *added_name)
{
    struct item *new = malloc(sizeof *new+strlen(added_name));
    if (!new) return false;
    strcpy(new->name,added_name);
    struct item *head = q->head;
    if(!head) q->tail = new;
    else head->next = new;
    q->head = new;
    new->next = 0;
    return true;
}

enum bool dequeue(struct queue *q, char *out)
{
    if(!q->tail) return false;
    struct item *head = q->head, *tail = q->tail, *free_ = 0;
    strcpy(out, tail->name);
    free_ = tail;
    tail = tail->next;
    free(free_);
    return true;
}

int main()
{
    char out[100];
    struct queue *q = {0};
    enqueue(&q,"first");
    enqueue(&q,"second");
    enqueue(&q,"third");
    dequeue(&q, &out);
    return 0;
}
