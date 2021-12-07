#include<stdio.h>
#include<stdlib.h>
struct node_t
{
    int value;
    struct node_t *next, *prev;
};

int is_cyclic(struct node_t *node)
{
    struct node_t *slow = node, *fast = node;

    while(1)
    {
        if(!fast || !fast->next || !fast->next->next) return 0;
        fast = fast->next->next;
        slow = slow->next;

        if(fast->value == slow->value)
        {
            struct node_t *curr_cycle = slow;

            while(1)
            {
                if(slow == node) return 1;
                if(slow == curr_cycle) return 0;
                slow = slow->next;
            }
        }

    }
}

struct node_t * add(struct node_t *list, int value)
{
    struct node_t *new_node = malloc(sizeof *new_node), *start = list;
    new_node->next = new_node->prev = NULL;
    new_node->value = value;

    if(!list) return new_node;

    for(;list->next;list = list->next);

    list->next = new_node;
    new_node->prev = list;

    return start;
}


void make_cycle(struct node_t ** list)
{
    if(!(*list)) return;

    struct node_t *curr = *list;

    for(;curr->next;curr = curr->next);

    curr->next = *list;
    (*list)->next = curr;
}




int main()
{
    struct node_t *list = add(NULL, 1);
    list = add(list, 2);
    list = add(list, 3);
    list = add(list, 4);
    list = add(list, 5);
    list = add(list, 6);
    list = add(list, 7);

    int a = is_cyclic(list);

    make_cycle(&list);

    a = is_cyclic(list);
    return 0;
}
