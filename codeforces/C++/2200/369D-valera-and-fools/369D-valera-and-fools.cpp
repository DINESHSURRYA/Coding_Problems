
#include <bits/stdc++.h>
using namespace std;

#define FAST ios::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    FAST

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> attacked(m);
    vector<bool> marked(n + 1, false);

    for (int i = 0; i < m; i++) {
        cin >> attacked[i];
        marked[attacked[i]] = true;
    }

    // Step 1: Remove unnecessary leaves
    vector<int> deg(n + 1);

    queue<int> q;

    for (int i = 1; i <= n; i++) {
        deg[i] = adj[i].size();

        if (deg[i] == 1 && !marked[i]) {
            q.push(i);
        }
    }

    vector<bool> removed(n + 1, false);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        removed[u] = true;

        for (int v : adj[u]) {
            if (!removed[v]) {
                deg[v]--;

                if (deg[v] == 1 && !marked[v]) {
                    q.push(v);
                }
            }
        }
    }

    // Step 2: Count edges in the remaining subtree
    int edges = 0;

    for (int u = 1; u <= n; u++) {
        if (!removed[u]) {
            for (int v : adj[u]) {
                if (!removed[v] && u < v) {
                    edges++;
                }
            }
        }
    }

    // BFS returning distances from source
    auto bfs = [&](int src) {
        vector<int> dist(n + 1, -1);
        queue<int> qu;

        dist[src] = 0;
        qu.push(src);

        while (!qu.empty()) {
            int u = qu.front();
            qu.pop();

            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    qu.push(v);
                }
            }
        }

        return dist;
    };

    // Step 3: Find one endpoint of the marked-node diameter
    vector<int> d = bfs(attacked[0]);

    int A = attacked[0];

    for (int u : attacked) {
        if (d[u] > d[A]) {
            A = u;
        }
    }

    // Step 4: Find the other endpoint
    vector<int> da = bfs(A);

    int B = A;

    for (int u : attacked) {
        if (da[u] > da[B]) {
            B = u;
        }
    }

    // Step 5: Calculate distances from B
    vector<int> db = bfs(B);

    // Step 6: Find optimal starting city
    int ans = -1;
    int best = -1;

    for (int u = 1; u <= n; u++) {
        if (!removed[u]) {
            int cur = max(da[u], db[u]);

            if (cur > best || (cur == best && u < ans)) {
                best = cur;
                ans = u;
            }
        }
    }

    // Minimum time = 2 * edges - maximum distance
    int minTime = 2 * edges - best;

    cout << ans << '\n';
    cout << minTime << '\n';

    return 0;
}
