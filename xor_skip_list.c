#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct list
{
    struct list *prev, *next;
    int data;
    struct list **skip;
};

void* xor(void* a, void* b)
{
    return (void*)((long unsigned int)a ^ (long unsigned int)b);
}

int find_length(struct list *list)
{
    int out = 0;
    for(;list;list = list->next)
        out++;
    return out;
}

void print_list(struct list* list)
{
    int length_of_list = find_length(list);

    struct list *first = list, *prev = NULL;

    for(struct list* curr_item = list; curr_item; curr_item = curr_item->next)
    {
        printf("*=%p d=%d next=%p skip_next=%p\n", curr_item, curr_item->data, curr_item->next, curr_item->skip);

        if(curr_item->skip)
            printf(" skip[0]=%p", curr_item->skip);

        puts("");
    }
}

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

    int length_of_list = find_length(list);

    if(list->data >= new_item->data)
    {
        list->prev = new_item;
        new_item->next = list;
        r_pointer = new_item;
        goto skip_other;
    }
    struct list *prev = NULL;
    for(struct list *curr_item = list; curr_item;)
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

        if(length_of_list%2 == 0)
        {
            if(curr_item->skip == NULL)break;
            curr_item = curr_item->skip[0];

        }

        else
        {
            struct list **skip = xor(curr_item->skip, prev);
            if(skip == NULL) break;
            prev = curr_item;
            curr_item = skip[0];
        }

    }

    label:;

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
                break;
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

    prev = NULL;
    for(struct list *curr_item = r_pointer; curr_item ;curr_item = curr_item->next)
    {
        if (!length_of_list%2)
            free(curr_item->skip);

        curr_item->skip = NULL;
    }


    struct list *last_item;
    for(struct list *curr_item = r_pointer; curr_item ;)
    {
        last_item = curr_item;
        if(curr_item->next && curr_item->next->next)
        {
            curr_item->skip = malloc(sizeof(curr_item->skip));
            curr_item->skip[0] = curr_item->next->next;
            curr_item = curr_item->skip[0];
        }
        else
            break;
    }

    if(length_of_list%2)
        last_item = last_item->next;

    for(struct list *curr_item = last_item; curr_item ;)
    {
        if (curr_item->prev && curr_item->prev->prev)
        {
            if (length_of_list % 2)
            {
                curr_item->skip = malloc(sizeof(curr_item->skip));
                curr_item->skip[0] = curr_item->prev->prev;
                curr_item = curr_item->skip[0];
            }
            else
            {
                struct list **prev_skip = malloc(sizeof(curr_item->skip));
                prev_skip[0] = curr_item->prev->prev;
                curr_item->skip = xor(curr_item->skip, prev_skip);
                curr_item = prev_skip[0];
            }
        }
        else
            break;
    }
    return r_pointer;
}


int main()
{
    struct list* list = NULL;
    list = add(list, 1);
    list = add(list, 12);
    list = add(list, 7);
    list = add(list, 3);
    list = add(list, 6);
    print_list(list);
    return 0;
}
