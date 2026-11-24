#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int MAXA = 2000005;

int spf[MAXA];
vector<int> primes;

void sieve() {
    for (int i = 2; i < MAXA; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            long long prod = 1LL * i * p;
            if (prod >= MAXA) break;
            spf[prod] = p;
            if (i % p == 0) break;
        }
    }
}

vector<int> get_distinct_primes(int x) {
    vector<int> res;
    while (x > 1) {
        int p = spf[x];
        res.push_back(p);
        while (x % p == 0) {
            x /= p;
        }
    }
    return res;
}

int n, q;
vector<int> a;
vector<vector<int>> adj;
vector<int> ans;
vector<vector<pair<int, int>>> prime_stack; // prime -> stack of {depth, node}

void dfs(int u, int parent, int depth) {
    vector<int> pf = get_distinct_primes(a[u]);

    int best_depth = -1;
    int best_node = -1;

    for (int p : pf) {
        if (!prime_stack[p].empty()) {
            auto [d, cand] = prime_stack[p].back();
            if (d > best_depth) {
                best_depth = d;
                best_node = cand;
            }
        }
    }
    ans[u] = best_node;

    for (int p : pf) {
        prime_stack[p].push_back({depth, u});
    }

    for (int v : adj[u]) {
        if (v != parent) {
            dfs(v, u, depth + 1);
        }
    }

    for (int p : pf) {
        prime_stack[p].pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    if (!(cin >> n >> q)) return 0;

    a.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ans.assign(n + 1, -1);
    prime_stack.assign(MAXA, {});

    bool dirty = true;

    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int v;
            cin >> v;
            if (dirty) {
                dfs(1, 0, 0);
                dirty = false;
            }
            cout << ans[v] << '\n';
        } else {
            int v, w;
            cin >> v >> w;
            a[v] = w;
            dirty = true;
        }
    }

    return 0;
}