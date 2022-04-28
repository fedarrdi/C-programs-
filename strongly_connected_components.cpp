#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 1e5;
vector<int> e[MAX];
vector<int> p[MAX];
queue<int> nodes;

int enter_time[MAX], exit_time[MAX];

void dfs_calc_times(int curr, int *max)
{
    enter_time[curr] = ++(*max);

    for(auto next : e[curr])
      if(!enter_time[next])
          dfs_calc_times(next, max);

    exit_time[curr] = ++(*max);
}

void visit_every_node(int n)
{
    int max = 0;
    for (int i = 1; i <= n; i++)
        if (!enter_time[i])
            dfs_calc_times(i, &max);
}

void create_reverse_graph(int n)
{
    for(int i = 1;i <= n;i++)
        for(auto curr : e[i])
            p[curr].push_back(i);
}

struct packet
{
    int i, exit_time;
} packets[MAX];

bool cmp_function(packet a, packet b)
{
    return a.exit_time > b.exit_time;
}

void push_in_stack(int n)
{
    for(int i = 0;i < n;i++)
    {
        packets[i].i = i + 1;
        packets[i].exit_time = exit_time[i + 1];
    }
    int len =  sizeof(packets) / sizeof(packets[0]);
    sort(packets, packets + len, cmp_function);

    for(int i = 0;i < n;i++)
        nodes.push(packets[i].i);

}

bool vis[MAX];
void dfs_print_component(int curr)
{
    vis[curr] = true;
    cout << curr << endl;
    for(auto next : p[curr])
        if(!vis[next])
            dfs_print_component(next);
}

void get_components()
{
    int component_index = 0;
    while(!nodes.empty())
    {
        int v = nodes.front();
        nodes.pop();
        if(!vis[v])
        {
            cout << "component: " << component_index++ << endl;
            dfs_print_component(v);
            cout << endl;
        }
    }
}

void print_queue()
{
    while(!nodes.empty())
    {
        int v = nodes.front();
        nodes.pop();
        cout << v << endl;
    }
}

int main()
{
    int n, m;
    cin  >> n >> m;
    for(int i = 0 ;i < m;i++)
    {
        int from, to;
        cin  >>  from  >> to;
        e[from].push_back(to);
    }

    visit_every_node(n);
    create_reverse_graph(n);
    push_in_stack(n);
    get_components();
    //print_queue();
    return 0;
}

/**
 8 11
 1 2
 2 3
 3 4
 3 5
 5 3
 6 5
 1 6
 6 7
 8 5
 2 6
 7 1
 */#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 1e5;
vector<int> e[MAX];
vector<int> p[MAX];
queue<int> nodes;

int enter_time[MAX], exit_time[MAX];

void dfs_calc_times(int curr, int *max)
{
    enter_time[curr] = ++(*max);

    for(auto next : e[curr])
      if(!enter_time[next])
          dfs_calc_times(next, max);

    exit_time[curr] = ++(*max);
}

void visit_every_node(int n)
{
    int max = 0;
    for (int i = 1; i <= n; i++)
        if (!enter_time[i])
            dfs_calc_times(i, &max);
}

void create_reverse_graph(int n)
{
    for(int i = 1;i <= n;i++)
        for(auto curr : e[i])
            p[curr].push_back(i);
}

struct packet
{
    int i, exit_time;
} packets[MAX];

bool cmp_function(packet a, packet b)
{
    return a.exit_time > b.exit_time;
}

void push_in_stack(int n)
{
    for(int i = 0;i < n;i++)
    {
        packets[i].i = i + 1;
        packets[i].exit_time = exit_time[i + 1];
    }
    int len =  sizeof(packets) / sizeof(packets[0]);
    sort(packets, packets + len, cmp_function);

    for(int i = 0;i < n;i++)
        nodes.push(packets[i].i);

}

bool vis[MAX];
void dfs_print_component(int curr)
{
    vis[curr] = true;
    cout << curr << endl;
    for(auto next : p[curr])
        if(!vis[next])
            dfs_print_component(next);
}

void get_components()
{
    int component_index = 0;
    while(!nodes.empty())
    {
        int v = nodes.front();
        nodes.pop();
        if(!vis[v])
        {
            cout << "component: " << component_index++ << endl;
            dfs_print_component(v);
            cout << endl;
        }
    }
}

void print_queue()
{
    while(!nodes.empty())
    {
        int v = nodes.front();
        nodes.pop();
        cout << v << endl;
    }
}

int main()
{
    int n, m;
    cin  >> n >> m;
    for(int i = 0 ;i < m;i++)
    {
        int from, to;
        cin  >>  from  >> to;
        e[from].push_back(to);
    }

    visit_every_node(n);
    create_reverse_graph(n);
    push_in_stack(n);
    get_components();
    //print_queue();
    return 0;
}

/**
 8 11
 1 2
 2 3
 3 4
 3 5
 5 3
 6 5
 1 6
 6 7
 8 5
 2 6
 7 1
 */
