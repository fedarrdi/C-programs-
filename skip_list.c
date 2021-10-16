#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct list
{
    struct list *prev, *next;
    int data;
    struct list **skip;///dynamic array
};

struct list* add(struct list *list, int data)
{
    struct list *r_pointer = list;
    struct list *new_item = malloc(sizeof(*new_item));
    new_item->data = data;
    new_item->prev = NULL;
    new_item->skip = NULL;
    new_item->next = NULL;
    if(!list)
        return new_item;

    ///if the item is the smallest one in the list
    if(list->data > new_item->data)
    {
        list->prev = new_item;
        new_item->next = list;
        r_pointer = new_item;
        goto skip_other;
    }

    for(struct list *curr_item = list; curr_item; curr_item = curr_item->skip)
    {
        if(new_item->data < curr_item->data)
            for(struct list *interval_item = curr_item; interval_item; interval_item = interval_item->prev)
                if(interval_item->data < new_item->data)
                {
                    struct list *prev_next_inter_item = interval_item->next;
                    interval_item->next = new_item;
                    new_item->prev = interval_item;
                    new_item->next = prev_next_inter_item;
                    prev_next_inter_item->prev = new_item;
                    goto label;
                }
        label: break;
    }

    struct list *tmp;
    if(!new_item->next)
    {
        for(tmp = list; tmp; tmp = tmp->next)
        {
            if(new_item->data < tmp->data)
            {
                struct list *old_prev_item = tmp->prev;
                new_item->next = tmp;
                tmp->prev = new_item;
                old_prev_item->next = new_item;
                new_item->prev = old_prev_item;
            }
            if(!tmp->next) break;
        }
    }

    if(!new_item->next)
    {
        tmp->next = new_item;
        new_item->prev = tmp;
    }
    skip_other:;

    ///removing all skips
    for(struct list *curr_item = new_item; curr_item ;curr_item = curr_item->next)
    {
        if (curr_item->skip)
        {
            free(curr_item->skip);
            curr_item->skip = NULL;
        }
    }

    for(struct list *curr_item = new_item; curr_item ;)
    {
        if(curr_item->next && curr_item->next->next)
        {
            curr_item->skip = malloc(sizeof(curr_item->skip));
            curr_item->skip[0] = curr_item->next->next;
            curr_item = curr_item->skip[0];
        }
        else
            break;///there are not enough element therefor we break
    }

    return r_pointer;
}

void print_list(struct list* list)
{
    for(struct list* curr_item = list; curr_item; curr_item = curr_item->next)
    {
        printf("*=%p d=%d next=%p skip=%p", curr_item, curr_item->data, curr_item->next, curr_item->skip);
        if(curr_item->skip)
            printf(" skip[0]=%p", curr_item->skip[0]);

        puts("");
    }
}


int main()
{
    struct list* list = NULL;
    list = add(list, 7);
    list = add(list, 48);
    list = add(list, 27);
    list = add(list, 3);
    list = add(list, 41);
    list = add(list, 1);
    print_list(list);
    return 0;
}
