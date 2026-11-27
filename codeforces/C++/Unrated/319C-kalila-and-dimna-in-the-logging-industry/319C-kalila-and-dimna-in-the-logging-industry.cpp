
#include <bits/stdc++.h>
using namespace std;

const int LOG = 18;
const int N = 100005;

vector<int> adj[N];
vector<int> atDepth[N];

int up[N][LOG];
int depth[N], tin[N], tout[N];
int timer = 0;

void dfs(int v, int p, int d) {
    depth[v] = d;
    tin[v] = ++timer;

    up[v][0] = p;

    for (int j = 1; j < LOG; j++) {
        up[v][j] = up[up[v][j - 1]][j - 1];
    }

    atDepth[d].push_back(tin[v]);

    for (int u : adj[v]) {
        if (u != p) {
            dfs(u, v, d + 1);
        }
    }

    tout[v] = timer;
}

int kthAncestor(int v, int k) {
    for (int j = 0; j < LOG; j++) {
        if (k & (1 << j)) {
            v = up[v][j];
        }
    }
    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> parent(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> parent[i];

        if (parent[i] != 0) {
            adj[parent[i]].push_back(i);
        }
    }

    // Build the forest.
    for (int i = 1; i <= n; i++) {
        if (parent[i] == 0) {
            dfs(i, 0, 0);
        }
    }

    cin >> m;

    while (m--) {
        int v, p;
        cin >> v >> p;

        if (p > depth[v]) {
            cout << 0 << ' ';
            continue;
        }

        int ancestor = kthAncestor(v, p);
        int targetDepth = depth[v];

        auto &vec = atDepth[targetDepth];

        int left = lower_bound(
            vec.begin(), vec.end(), tin[ancestor]
        ) - vec.begin();

        int right = upper_bound(
            vec.begin(), vec.end(), tout[ancestor]
        ) - vec.begin();

        // Exclude the queried person itself.
        cout << right - left - 1 << ' ';
    }

    cout << '\n';

    return 0;
}
