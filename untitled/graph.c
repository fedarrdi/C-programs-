//
// Created by radosalvfilipov on 3/17/22.
//
#include "structs.h"
#include "init_func.c"

int cmp_nodes(struct node *a, struct node *b)
{
    for(int i = 0;i < a->ull_count;i++)
        if(a->index[i] != b->index[i])
            return 0;
    return 1;
}

void add_child_to(struct node * parent, struct node * child)
{
    for(int i = 0;i < parent->children_count;i++)
        if(!cmp_nodes(parent->children[i], child))
            return;

    int children_arr_size = sizeof(parent->children) / sizeof (*child);

    int new_size = !parent->children_count ? 1 : 2 * parent->children_count;

    if(children_arr_size == parent->children_count)
        parent->children = realloc(parent->children, new_size);

    parent->children[parent->children_count++] = child;
}

void add_to_graph(struct graph *graph, struct node * curr)
{
    int size = sizeof(graph->node) / sizeof(*curr);

    int new_size = !graph->nodes_count ? 1 : 2 * graph->nodes_count;

    if(size == graph->nodes_count)
        graph->node = realloc( graph->node, new_size);

    graph->node[graph->nodes_count++] = curr;
}

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b= c;
}

int is_place_valid(struct board board, const struct point *pos)
{
    return pos->x >= 0 && pos->x < board.n && pos->y >= 0 && pos->y < board.m;
}

struct board generate_new_board(struct board board, struct point *delta_empty)///first time last_empty == board->empty
{
    struct point pos;

    if(!delta_empty->x && !delta_empty->y)
    {
        pos.x = board.empty.x, pos.y = board.empty.y - 1;
        delta_empty->y = -1;

        if (is_place_valid(board, &pos))
        {
            swap(&board.data[board.empty.y][board.empty.x], &board.data[pos.y][pos.x]);
            return board;
        }
    }

    if(!delta_empty->x && delta_empty->y == 1)
    {
        pos.x = board.empty.x + 1, pos.y = board.empty.y;
        delta_empty->x = 1, delta_empty->y = 0;

        if (is_place_valid(board, &pos))
        {
            swap(&board.data[board.empty.y][board.empty.x], &board.data[pos.y][pos.x]);
            return board;
        }
    }

    if(delta_empty->x == 1 && !delta_empty->y)
    {
        pos.x = board.empty.x, pos.y = board.empty.y + 1;
        delta_empty->x = 0, delta_empty->y = 1;

        if (is_place_valid(board, &pos))
        {
            swap(&board.data[board.empty.y][board.empty.x], &board.data[pos.y][pos.x]);
            return board;
        }
    }

    if(!delta_empty->x && delta_empty->y == 1)
    {
        pos.x = board.empty.x - 1, pos.y = board.empty.y;
        delta_empty->y = delta_empty->x = 1;

        if (is_place_valid(board, &pos))
        {
            swap(&board.data[board.empty.y][board.empty.x], &board.data[pos.y][pos.x]);
            return board;
        }
    }
}

void generate_graph(struct board board)
{
    struct point delta = {0, 0};

    while(delta.x && delta.y)
    {
        struct board new_board = generate_new_board(board, &delta);

        /// generirame nov node s board

        generate_graph(new_board);
    }
}
