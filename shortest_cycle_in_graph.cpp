#include <iostream>

using namespace std;

#define INF 10000

int n, m;

const int MAX_N = 300;

int dp[MAX_N][MAX_N][MAX_N];

int min(int a, int b) { return a < b ? a : b; }

int main()
{
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

    int best_weight_path = INF;
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
                    best_weight_path = curr_path_weight;
            }
        }
    }

    cout << best_weight_path << endl;

    return 0;
}
/*
5 7
1 2 1
1 3 1
1 4 1
2 4 3
2 5 4
2 3 1
4 5 7
*/
