#include<stdio.h>
struct item
{
    struct item *p_xor_n;
    int data;
};

void* xor(void* a, void* b)
{
    return (void*)((long unsigned int)a ^ (long unsigned int)b);
}

void add_item_back(struct item **list, struct item *new_item)
{
    struct item *start = *list;

    if (!(*list))
    {
        *list = new_item;
        return;
    }

    if (!(*list)->p_xor_n)
    {
        (*list)->p_xor_n = new_item;
        return;
    }

    struct item *prev = *list;
    *list = (*list)->p_xor_n;

    if(!(*list)->p_xor_n)
    {
        new_item->p_xor_n = *list;
        (*list)->p_xor_n = xor(prev, new_item);
        *list = start;
        return;
    }

    while(xor((*list)->p_xor_n, prev))
    {
        struct item *tmp = *list;
        *list = xor((*list)->p_xor_n, prev);
        prev = tmp;
    }

    new_item->p_xor_n = *list;
    (*list)->p_xor_n = xor((*list)->p_xor_n, new_item);
    *list = start;
}


void pop_list(struct item **list)
{
    struct item *start = *list, *prev = 0;

    if((unsigned long long)xor((*list)->p_xor_n, prev) <= 1000)
    {
        *list = NULL;
        return;
    }

    while(xor((*list)->p_xor_n, prev))
    {
        struct item *tmp = *list;
        *list = xor((*list)->p_xor_n, prev);
        prev = tmp;
    }

    (*list)->p_xor_n = 0;
    struct item *tmp = *list;
    *list = prev;
    (*list)->p_xor_n = xor((*list)->p_xor_n, tmp);
    *list = start;
}

void print_list(struct item *list)
{
    if(!list)
    {
        printf("No elements!!!\n");
        return;
    }
    struct item *prev = 0;

    while(xor(list->p_xor_n, prev))
    {
        struct item *tmp = list;
        printf("%d\n", list->data);
        list = xor(list->p_xor_n, prev);
        prev = tmp;
    }
    printf("%d\n", list->data);
}

struct item *search_item(struct item *list, int data)
{
    struct item *prev = 0;

    while(xor(list->p_xor_n, prev))
    {
        if(list->data == data)
            return list;

        struct item *tmp = list;
        list = xor(list->p_xor_n, prev);
        prev = tmp;

    }

    if(list->data == data)
        return list;

    printf("This item does not exist!!!");
    return 0;
}


void add_after(struct item **list, const struct item *after_item, struct item *new_item)
{
    struct item *start = *list;

    struct item *prev = 0;

    while(xor((*list)->p_xor_n, prev))
    {
        struct item *tmp = *list;
        /**
         *
         *  NOT READY
         *
         */
        *list = xor((*list)->p_xor_n, prev);
        prev = tmp;
    }

    if(after_item->data == (*list)->data)
        add_item_back(list, new_item);

    *list = start;
}


void split_list(struct item **list, struct item *left, struct item *right, struct item *split_address)
{
    struct item *prev = 0;
    while(xor((*list)->p_xor_n, prev))
    {
        struct item *tmp = *list;

        if(split_address == *list)
        {
            
        }

        *list = xor((*list)->p_xor_n, prev);
        prev = tmp;
    }
}



int main()
{
    struct item *list = 0;
    struct item new_item = {0, 1};
    add_item_back(&list, &new_item);

    struct item new_item2 = {0, 2};
    add_item_back(&list, &new_item2);

    struct item new_item3 = {0, 3};
    add_item_back(&list, &new_item3);

    struct item new_item4 = {0, 4};
    add_item_back(&list, &new_item4);

    struct item new_item5 = {0, 5};
    add_item_back(&list, &new_item5);

    struct item new_item6 = {0, 6};
    add_item_back(&list, &new_item6);

    struct item new_item7 = {0, 7};
    add_item_back(&list, &new_item7);

    print_list(list);

    struct item *s_l = search_item(list, 6);

    pop_list(&list);
    pop_list(&list);
    pop_list(&list);
    pop_list(&list);
    pop_list(&list);
    pop_list(&list);
    pop_list(&list);

    print_list(list);

    return 0;
}

