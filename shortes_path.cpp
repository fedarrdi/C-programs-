#include<iostream>
#include<vector>

using namespace std;

const int MAX = 1e4;

vector<int> e[MAX];
vector<int> w[MAX];

vector<int>path;
int dist[MAX];

bool dfs(int curr, int end, int depth)
{
    if(curr == end) 
    {
        path.clear();
        return true;
    }

    for(int i = 0;i < e[curr].size();i++)
    {
        int child = e[curr][i];
        int curr_dist = dist[curr] + w[curr][i];
        
        if(dist[child] > curr_dist || dist[child] == -1)
        {
            dist[child] = curr_dist;
            if(dfs(child, end, depth + 1))
            {
                path.push_back(child);
                if(depth)
                    return true;
            }
        }
    }

    return false;
}

int main()
{
    int n, m;
    cin >> n >> m;

    for(int i = 0;i < m;i++)
    {
        int a, b, l;
        cin >> a >> b >> l;
        e[a].push_back(b);
        e[b].push_back(a);
        w[a].push_back(l);
        w[b].push_back(l);
    }
    
    int start, end;
    cin >> start >> end;


    for(int i = 1;i <= n;i++)  dist[i] = -1;
    dist[start] = 0;
    dfs(start, end, 0);
    if(dist[end] > 0)
    {
        for(int c : path)
            cout << c << " ";
        cout << start << " ";

    }
    else
        cout << "no path!!!" << endl;
    
    
    return 0;
}
