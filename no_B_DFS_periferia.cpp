#include<iostream>
#include<vector>

using namespace std;

vector<int> e[100000];

int dist[100000];

void dfs(int curr)
{
    for (int child : e[curr])
    {
        int curr_dist = dist[curr] + 1;
        if(dist[child] > curr_dist)
        {
            dist[child] = curr_dist;
            dfs(child);
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, c, r;
    cin >> n >> m >> c >> r;


    for(int i = 0;i < m;i++)
    {
        int a, b;
        cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);

    }
    
    for(int i = 1;i <= n;i++)
        dist[i] = 1000000;

    dist[c] = 0;

    dfs(c);

    int ans = 0;
    for(int i = 1;i <= n;i++)
        if(dist[i] > r)
            ans++;

    cout << ans << endl;
    for(int i = 1;i <= n;i++)
        if(dist[i] > r)
            cout  <<  i << "\n";


    return 0;
}
