#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

#define INF 10000;

const int MAX_N = 303;

long long dp[MAX_N][MAX_N][MAX_N];

//priema samo validni putishta
void getpath(int f, int t, int k, vector<int> &path)
{
    if (f == t) 
    {
        path.push_back(f);
        return;
    }
    
    if (k == 0)
    {
        path.push_back(f);
        path.push_back(t);
        return;
    }

    if(dp[f][t][k] < dp[f][t][k - 1])
    {
        //izpolzvame k
        getpath(f, k, k-1, path);
        path.pop_back(); // mahame k
        //f -> ... -> u -> k
        //f -> ....-> u
        //k -> .... -> t
        getpath(k, t, k-1, path);
    }
    
    else
    {
        getpath(f, t, k-1, path);
    }
}

int n, m;

vector<int> getpath(int f, int t) 
{
    vector<int> path;
    getpath(f, t, n, path);
    return path;
}

int main()
{
    cin >> n >> m;
    
                
    for(int y = 0;y <= n;y++)
        for(int x = 0;x <= n;x++)
            dp[y][x][0] = INF; 
    
    for(int i = 1;i <= n;i++)
        dp[i][i][0] = 0;
    
    for(int i = 0;i < m;i++)
    {
        int f, t, w;
        cin >> f >> t >> w;
        dp[f][t][0] = w;
        dp[t][f][0] = w;
    }

    for(int k = 1;k <= n;k++)
    {
        for(int v = 1; v <= n;v++)
        {
            for(int  x = 1;x <= n;x++)
            {
                dp[v][x][k] = min(
                                dp[v][x][k - 1],
                                dp[v][k][k - 1] + dp[k][x][k - 1]
                                );
            }
        }
    }

    cout << endl;
    for(int k = 0;k <= n;k++)
    {
        for(int y = 1;y <= n;y++)
        {
            for(int x = 1;x <= n;x++)
            {
                cout << dp[y][x][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }


    int q;
    cin  >> q;
    for(int i = 0;i < q;i++)
    {
        int f, t;
        cin >> f >> t;
        cout << f <<  "----> " << t << " " << dp[f][t][n] << endl;

        auto path = getpath(f, t);
        for (int x : path) {
            cout << x << ' ';
        }
        cout << endl;
    }

    return 0;
}
