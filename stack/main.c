#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <malloc.h>

struct item
{
    struct item *next;
    char name[1];
};

enum bool { false, true } push(struct item **p,const char *added_name)
{
    struct item *new = malloc(sizeof *new+strlen(added_name));
    if (!new) return false;
    strcpy(new->name,added_name);
    new->next = *p;
    *p = new;
    return true;
}

enum bool pop(struct item **p,char *out)
{
    if (!*p) return false;
    struct item *old_head = *p;
    strcpy(out,old_head->name);
    *p = (**p).next;
    free(old_head);
    return true;
}

void main()
{
    struct item *stack = 0;

    push(&stack,"first");
    push(&stack, "second");

    char buffer[100];
    pop(&stack,buffer);
    pop(&stack,buffer);
}