#include <stdio.h>
#include <string.h>
#include<stdlib.h>

struct point
{
    int x, y;
};

struct board
{
    int n, m;
    int ** data;
    struct point empty;
};

struct node
{
    int children_count;
    float ready_v;
    int ull_count;
    unsigned long long *index;
    struct node **children;
};

struct graph
{
    int nodes_count;
    struct node **node;
};

#include "structs.h"
#include<stdlib.h>

unsigned length(int n)
{
    unsigned l = 0;
    for(;n;n /= 10, l++);
    return l;
}
int number_of_bits_in(int n)
{
    long long p = 1, out = 0;
    while(n >= p)
        p <<= 1, out++;
    return out;
}

unsigned long long number_of_bits_board(const struct board board)
{
    unsigned long long out = 0;
    for(int y = 0;y < board.n;y++)
        for (int x = 0; x < board.m; x++)
               out += number_of_bits_in(board.data[y][x]);
    return out;
}

void put_digits(unsigned long long *arr, struct board board)
{
    int idx = 0,i = 0;
    for(int y = 0;y < board.m;y++)
        for(int x = 0;x < board.n;x++)
        {
            int curr_v = board.data[y][x];
            for(int j = 0;j < number_of_bits_in(curr_v);j++, i++)
            {
                arr[idx] |= curr_v & 1 << i;
                if(i == sizeof (unsigned long long ) * 8) idx ++, i = 0;
            }
        }
}

unsigned long long *from_board_to_ind(const struct board board, struct node *node)
{
    int ull = number_of_bits_board(board);
    node->ull_count =  ull / (sizeof(unsigned long long) * 8) + 1;
    unsigned long long *ind = malloc(sizeof *ind * node->ull_count);
    put_digits(ind, board);
    return ind;
}

float from_board_to_ready_v(struct board board)
{
    int times = 0;
    for(int y = 0;y < board.n;y++)
        for(int x = 0;x < board.m;x++)
            times += (y * board.m + x == board.data[y][x] - 1);

    return (float)times / (float)(board.n * board.m);
}

struct node * init_node(const struct board board)
{
    struct node * new_node = malloc(sizeof *new_node);
    new_node->ready_v = from_board_to_ready_v(board);
    new_node->index = from_board_to_ind(board, new_node);
    return new_node;
}

struct board * init_board(int n, int m, struct point empty)
{
    struct board *new_board = malloc(sizeof *new_board);
    new_board->n = n;
    new_board->m = m;
    new_board->empty = empty;
    new_board->data = malloc(n * sizeof (**new_board->data));
    for(int i = 0;i < n;i++)
        new_board->data[i] = malloc(m * sizeof (**new_board->data));
    return  new_board;
}

size_t length_of(int n)
{
    int out = 0;
    while(n)
    {
        n /= 10;
        out++;
    }
    return out;
}

int cmp_nodes(const struct node *a,const struct node *b)
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

int check_exist(const struct graph * graph, struct node * curr)
{
    for(int i = 0;i < graph->nodes_count;i++)
        if(cmp_nodes(curr, graph->node[i]))
            return 1;
    return 0;
}


int A_star(struct board board, struct node *parent, struct graph *graph, struct graph *path)
{
    struct point delta = {0, 0};
    struct node *nodes[4];
    struct board boards[4];
    int count = 0;

    while(delta.x && delta.y)
    {
        struct board new_board = generate_new_board(board, &delta);
        struct node *new_node = init_node(new_board);

        if(check_exist(graph, new_node))
            free(new_node);
        else
        {
            nodes[count] = new_node;
            boards[count++] = new_board;
        }
    }
    int best_index = 0;

    for(int i = 1;i < count;i++)
        if(nodes[i]->ready_v > nodes[best_index]->ready_v)
            best_index = i;

    add_child_to(parent, nodes[best_index]);
    add_to_graph(graph, nodes[best_index]);

    if(nodes[best_index]->ready_v == 1) return 1;

    if(A_star(boards[best_index], nodes[best_index], graph, path))
    {
        add_to_graph(path, nodes[best_index]);
        return 1;
    }
}

struct board *read_file(char *file_name)
{
    char * line = NULL;
    size_t len = 0, read;
    int n = 0, m = 0;
    struct point empty;

    FILE *f = fopen(file_name, "r");
    if(!f) return 0;

    while ((read = getline(&line, &len, f)) != -1)
    {
        int index = 0, curr_n;
        m = 0;
        while (sscanf(line + index, "%d", &curr_n) != EOF)
        {
            index += length_of(curr_n) + 1;
            if(curr_n == 0)
                empty.y = m, empty.x = n;

            m++;
        }
        n++;
    }

    fclose(f);
    f = fopen(file_name, "r");
    if(!f) return 0;

    struct board *board = init_board(n, m, empty);
    line = NULL;
    len = 0;
    int y = 0;

    while ((read = getline(&line, &len, f)) != -1)
    {
        int index = 0, curr_n, x = 0;
        while (sscanf(line + index, "%d", &curr_n) != EOF)
        {
            index += length_of(curr_n) + 1;
            board->data[y][x] = curr_n;
            x++;
        }
        y++;
    }
    return board;
}

int main(int argc, char** argv)
{
    if(argc < 2) return 0;

    struct board *board = read_file(argv[1]);

    for(int i = 0;i < board->n;i++)
    {
        for (int j = 0; j < board->m; j++)
        {
            int curr = board->data[i][j];
            printf("%d ", curr);
        }
        printf("\n");
    }
    struct board cpy = *board;

    struct node *root = init_node(cpy);

    struct board *board1 = init_board(3, 3, (struct point){2,2});

    int p = 9;
    for(int y = 0;y < board1->n;y++)
        for(int x = 0;x < board1->m;x++)
            board1->data[y][x] = p--;

    board1->data[2][2] = 0;


    struct board b = *board1;
    struct node *other = init_node(b);


    /*struct graph *graph = {0, NULL};
    struct graph *path = (0, NULL);

    A_star(cpy, root, graph, path);*/

    return 0;
}
