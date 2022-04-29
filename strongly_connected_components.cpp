#include<iostream>
#include<vector>
#include<stack>

using namespace std;

const int MAX = 1e4;

vector<int> e[MAX];
vector<int> p[MAX];
stack<int> s;

bool vis[MAX];

void dfs(int curr)
{
    vis[curr] = true;
    for(auto next : e[curr])
        if(!vis[next])
            dfs(next);

    s.push(curr);
}

void visit_all(int n)
{
    for(int i = 1;i <= n;i++)
        if(!vis[i])
            dfs(i);
}

bool vis2[MAX];

void dfs_print(int curr)
{
    vis2[curr] = true;
    for(auto next : p[curr])
        if(!vis2[next])
            dfs_print(next);

    cout << curr << " ";
}

void find_strongly_connected_components()
{
    while(!s.empty())
    {
        int v = s.top();
        s.pop();

        if (!vis2[v])
        {
            dfs_print(v);
            cout << endl;
        }
    }
}


int main()
{
    int n, m;
    cin >> n >> m;

    for(int i = 0;i < m;i++)
    {
        int f, t;
        cin >> f >> t;
        e[f].push_back(t);
        p[t].push_back(f);
    }

    visit_all(n);
    find_strongly_connected_components();

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
