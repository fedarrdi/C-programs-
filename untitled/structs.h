//
// Created by radosalvfilipov on 3/17/22.
//

#ifndef UNTITLED_STRUCTS_H
#define UNTITLED_STRUCTS_H

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


#endif //UNTITLED_STRUCTS_H
