#include <stdio.h>
#include <stdlib.h>

struct node
{
    int children_count, number;
    struct node **children;
};

struct graph_nodes
{
    int nodes_count;
    struct node ** node;
};

void add_child_to(struct node * parent, struct node * child)
{
    for(int i = 0;i < parent->children_count;i++)
        if(parent->children[i]->number == child->number)
            return;


    int children_arr_size = sizeof(parent->children) / sizeof (*child);

    int new_size = !parent->children_count ? 1 : 2 * parent->children_count;

    if(children_arr_size == parent->children_count)
        parent->children = realloc(parent->children, new_size);

    parent->children[parent->children_count++] = child;
}

void print_node_children(struct node * curr)
{
    printf("number of children: %d\n", curr->children_count);
    for(int i = 0;i < curr->children_count;i++)
        printf("%d ------> %d\n", curr->number, curr->children[i]->number);
}

void print_graph(struct graph_nodes graph)
{
    for(int i = 0;i < graph.nodes_count;i++)
        print_node_children(graph.node[i]);
    printf("\n");
}

struct node * init_node(int number)
{
    struct node * new = malloc(sizeof * new);
    new->children_count = 0;
    new->number = number;
    new->children = NULL;
    return new;
}

void add_to_graph(struct graph_nodes *graph, struct node * curr)
{
    int size = sizeof(graph->node) / sizeof(*curr);

    int new_size = !graph->nodes_count ? 1 : 2 * graph->nodes_count;

    if(size == graph->nodes_count)
        graph->node = realloc( graph->node, new_size);

    graph->node[graph->nodes_count++] = curr;
}

void add_from_to(int from, int to, struct graph_nodes *graph)
{
    struct node *first = NULL, *second = NULL;

    for(int i = 0;i < graph->nodes_count;i++)
    {
        if(graph->node[i]->number == from)
            first = graph->node[i];

        if(graph->node[i]->number == to)
            second = graph->node[i];
    }

    if(!first)
    {
        first = init_node(from);
        add_to_graph(graph, first);
    }

    if(!second)
    {
        second = init_node(to);
        add_to_graph(graph, second);
    }

    add_child_to(first, second);
}


void write_to_file(struct graph_nodes graph, FILE *write)
{
    for(int i = 0;i < graph.nodes_count;i++)
    {
        for(int j = 0;j < graph.node[i]->children_count;j++)
        {
            int parent = graph.node[i]->number, child = graph.node[i]->children[j]->number;
            putw(parent, write);
            putw(child, write);
        }
    }
    fclose(write);
}

void make_graph(FILE *read, struct graph_nodes *graph)
{
    int num, a = 0, parent;
    while ( (num = getw(read)) != EOF )
    {
        if(!a) parent = num;

        else add_from_to(parent, num, graph);

        a = !a;
    }
    fclose(read);
}


int main(int argc, char *argv[])
{
    FILE *a;
    if(argc < 2) return 0;
    a = fopen(argv[1], "w");

    if(!a) return 0;

    struct graph_nodes graph = {0, NULL};
    add_from_to(1, 2, &graph);
    add_from_to(2, 1, &graph);
    add_from_to(3, 2, &graph);
    add_from_to(2, 3, &graph);
    add_from_to(1, 3, &graph);
    write_to_file(graph, a);

    add_from_to(3, 1, &graph);


    a = fopen(argv[1], "r");

    struct graph_nodes graph2 = {0, NULL};
    make_graph(a, &graph2);

    printf("graph1\n");
    print_graph(graph);

    printf("graph2\n");
    print_graph(graph2);

    return 0;
}
