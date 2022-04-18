#include <iostream>
#include <vector>
using namespace std;

#define INF 10000

const int MAX_N = 300;

int dp[MAX_N][MAX_N][MAX_N];

int min(int a, int b) { return a < b ? a : b; }

void get_path(int f, int t, int k, vector<int> &path)
{
    if(f == t)
    {
        path.push_back(f);
        return;
    }

    if(k == 0)
    {
        path.push_back(f);///moje i da trqbva da gi pushavam na obrtano
        path.push_back(t);
        return;
    }

    if(dp[f][t][k] < dp[f][t][k - 1])/// vzel sum tova dp[v][k][k - 1] + dp[k][x][k - 1]
    {
        get_path(f, k, k - 1, path);
        path.pop_back();
        get_path(k, t, k - 1, path);
    }
    else
    {//// v tozi sluchai dp[f][t][k] = dp[f][t][k - 1], zashtoto dp[f][t][k] nqma kak da e po - malko ot dp[f][t][k - 1]
        get_path(f, t, k - 1, path);
    }
}

void print_path(int f, int t, int n)
{
    vector<int> path;
    get_path(f, t, n, path);
    for(auto curr :  path)
        cout << curr << " ";
    cout << endl;
}


int main()
{
    int n, m;

    cin >> n >> m;

    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            dp[i][j][0] = INF;

    for(int i = 1;i <= n;i++)
        dp[i][i][0] = 0;

    for(int i = 0;i < m;i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        dp[u][v][0] = w;
        dp[v][u][0] = w;
    }

    for(int k = 1;k <= n;k++)
        for(int v = 1;v <= n;v++)
            for(int x = 1;x <= n;x++)
                dp[v][x][k] = min(dp[v][x][k-1], dp[v][k][k - 1] + dp[k][x][k - 1]);

    cout << endl;

    for(int k = 1;k <= n;k++)
    {
        for (int y = 1; y <= n; y++)
        {
            for (int x = 1; x <= n; x++)
            {
                cout << dp[y][x][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    /// shortest cycle

    vector<int> best_path;
    int best_weight_path = INF, a, b, c;
    for(int u = 1;u <= n;u++)
    {
        for(int v = 1;v <= n;v++)
        {
            if(u == v || dp[u][v][0] == INF) continue;

            for(int x = 1; x <= n;x++)
            {
                if(x == u || x == v || dp[x][u][0] == INF) continue;

                if(u < x || u < v) continue;

                int curr_path_weight = dp[x][v][u - 1] + dp[u][v][0] + dp[u][x][0];
                if(best_weight_path > curr_path_weight)
                {
                    best_path.clear();
                    get_path(x, v, u - 1, best_path);
                    a = x, b = v, c = u;
                    best_weight_path = curr_path_weight;
                }
            }
        }
    }
    for(auto curr : best_path)
        cout << curr << " ";
    cout << endl;

    cout << best_weight_path << endl;


    cout << endl << endl << endl;

    ///shortest dist from to
    for(int v = 1; v <= n; v++)
    {
        for(int  x = 1; x<= n; x++)
        {
            if(v == x) continue;
            cout << "dist from " << v << " to " << x << " = " << dp[v][x][n] << endl;
            print_path(v, x, n);
        }
    }

    return 0;
}

/*
5 7
1 2 1
1 4 1
2 3 1
2 6 100
3 5 1
5 4 1
4 6 100
*/
