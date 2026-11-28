
#include <bits/stdc++.h>
using namespace std;

#define FAST ios::sync_with_stdio(false); cin.tie(nullptr);

const int N = 100005;
const int LOG = 20;

vector<int> adj[N], depthNodes[N];

int up[N][LOG];
int depth[N], tin[N], tout[N];
int timer = 0;

void dfs(int u, int p)
{
    tin[u] = ++timer;

    depthNodes[depth[u]].push_back(tin[u]);

    up[u][0] = p;

    for (int j = 1; j < LOG; j++)
        up[u][j] = up[up[u][j - 1]][j - 1];

    for (int v : adj[u])
    {
        if (v == p) continue;

        depth[v] = depth[u] + 1;
        dfs(v, u);
    }

    tout[u] = timer;
}

int kthAncestor(int u, int k)
{
    for (int j = 0; j < LOG; j++)
    {
        if (k & (1 << j))
            u = up[u][j];

        if (u == 0)
            return 0;
    }

    return u;
}

int main()
{
    FAST

    int n;
    cin >> n;

    vector<int> roots;

    for (int i = 1; i <= n; i++)
    {
        int p;
        cin >> p;

        if (p == 0)
            roots.push_back(i);
        else
            adj[p].push_back(i);
    }

    for (int root : roots)
        dfs(root, 0);

    int m;
    cin >> m;

    while (m--)
    {
        int v, p;
        cin >> v >> p;

        int a = kthAncestor(v, p);

        if (a == 0)
        {
            cout << 0 << " ";
            continue;
        }

        int d = depth[v];

        auto &vec = depthNodes[d];

        int l = lower_bound(vec.begin(), vec.end(), tin[a])
                - vec.begin();

        int r = upper_bound(vec.begin(), vec.end(), tout[a])
                - vec.begin();

        cout << r - l - 1 << " ";
    }

    cout << '\n';

    return 0;
}
