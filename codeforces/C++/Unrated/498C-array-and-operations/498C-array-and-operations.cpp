#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int cap;
    int flow;
    int rev;
};

struct Dinic {
    int n;
    vector<vector<Edge>> adj;
    vector<int> level;
    vector<int> ptr;

    Dinic(int n) : n(n), adj(n), level(n), ptr(n) {}

    void add_edge(int from, int to, int cap) {
        adj[from].push_back({to, cap, 0, (int)adj[to].size()});
        adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &edge : adj[v]) {
                if (edge.cap - edge.flow > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[v] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int v, int t, int pushed) {
        if (pushed == 0 || v == t) return pushed;
        for (int &cid = ptr[v]; cid < adj[v].size(); ++cid) {
            auto &edge = adj[v][cid];
            int tr = edge.to;
            if (level[v] + 1 != level[tr] || edge.cap - edge.flow == 0) continue;
            int tr_pushed = dfs(tr, t, min(pushed, edge.cap - edge.flow));
            if (tr_pushed == 0) continue;
            edge.flow += tr_pushed;
            adj[tr][edge.rev].flow -= tr_pushed;
            return tr_pushed;
        }
        return 0;
    }

    int max_flow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, t, 1e9)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

int count_prime_powers(int val, int p) {
    int cnt = 0;
    while (val > 0 && val % p == 0) {
        cnt++;
        val /= p;
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> a(n + 1);
    set<int> primes;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        int temp = a[i];
        for (int d = 2; d * d <= temp; ++d) {
            if (temp % d == 0) {
                primes.insert(d);
                while (temp % d == 0) temp /= d;
            }
        }
        if (temp > 1) {
            primes.insert(temp);
        }
    }

    vector<pair<int, int>> pairs(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (u % 2 == 0) swap(u, v); // Ensure u is odd, v is even
        pairs[i] = {u, v};
    }

    int total_operations = 0;
    int S = 0, T = n + 1;

    for (int p : primes) {
        Dinic dinic(n + 2);

        for (int i = 1; i <= n; ++i) {
            int cnt = count_prime_powers(a[i], p);
            if (cnt > 0) {
                if (i % 2 == 1) {
                    dinic.add_edge(S, i, cnt);
                } else {
                    dinic.add_edge(i, T, cnt);
                }
            }
        }

        for (auto &pr : pairs) {
            dinic.add_edge(pr.first, pr.second, 1e9);
        }

        total_operations += dinic.max_flow(S, T);
    }

    cout << total_operations << "\n";

    return 0;
}