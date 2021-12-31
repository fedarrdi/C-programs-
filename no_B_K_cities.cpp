#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

const int MAX = 1e4 + 3;

vector<int> e[MAX];
vector<int> out;

bool vis[256000000];

int P, M, K;

void dfs(int curr)
{
    vis[curr] = true;

    if(e[curr].size() >= K)
        out.push_back(curr);

    for(int child : e[curr])
        if(!vis[child])
            dfs(child);
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL) ;

    cin >> P >> M;
    int first;
    for(int i = 0;i < M;i++)
    {
        int a, b;
        cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);
        first = a;
    }
    cin >> K;
    dfs(first);

    sort(out.begin(), out.end());

    cout << out.size() << "\n";
    for(int i : out)
        cout << i <<  " ";
    return 0;
}
