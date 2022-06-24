#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct dairy
{
    float fat_content, liters;
    char name[1];
};

struct dairy * create_dairy(float fat_content, float liters, const char *name)
{
    struct dairy *new_dairy_product = malloc(sizeof *new_dairy_product + strlen(name));
    if(!new_dairy_product) return NULL;

    new_dairy_product->fat_content = fat_content;
    new_dairy_product->liters = liters;
    strcpy(new_dairy_product->name, name);

    return new_dairy_product;
}


struct fruits
{
    float weight;
    char color[1];
};

struct fruits * create_fruit(float weight, const char *color)
{
    struct fruits *new_fruit_product = malloc(sizeof *new_fruit_product + strlen(color));
    if(!new_fruit_product) return NULL;

    new_fruit_product->weight = weight;
    strcpy(new_fruit_product->color, color);

    return new_fruit_product;
}

enum item_type {DAIRY, FRUIT};

struct item
{
    enum item_type type;
    union
    {
        struct dairy *milk;
        struct fruits *apple;
    };
};

struct node
{
    struct item *item;
    struct node *next, *prev;
};


struct node *add_node(struct node *head, void *item_type_ptr, enum item_type new_item_type)
{

    struct item *new_item = malloc(sizeof *new_item);
    if(!new_item || !item_type_ptr) return head;

    new_item->type = new_item_type;

    if (new_item_type == DAIRY)
        new_item->milk = item_type_ptr;

    if (new_item_type == FRUIT)
        new_item->apple = item_type_ptr;

    struct node *new_node = malloc(sizeof *new_node);
    if(!new_node) return head;

    new_node->item = new_item;
    new_node->next = new_node->prev = NULL;

    if(!head) return new_node;

    struct node *start = head;
    for(; start->next; start = start->next);
    start->next = new_node;

    return head;
};

int main()
{
    struct dairy *first_dairy = create_dairy(3.5, 1.5, "greek yogurt");
    struct fruits *first_fruit = create_fruit(0.2, "red");
    struct dairy *second_dairy = create_dairy(4.5, 2, "milk");
    struct fruits *second_fruit = create_fruit(0.5, "yellow");

    struct node *list = NULL;
    list = add_node(list, first_dairy, DAIRY);
    list = add_node(list, first_fruit, FRUIT);
    list = add_node(list, second_dairy, DAIRY);
    list = add_node(list, second_fruit, FRUIT);

    return 0;
}
