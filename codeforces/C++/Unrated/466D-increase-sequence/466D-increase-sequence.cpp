#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

using namespace std;

const long long INF = 1e9;

struct Component {
    long long weight_sum;
    long long size;
    int root;

    bool operator<(const Component& other) const {
        if (size != other.size)
            return size > other.size; // Descending order of size
        return root < other.root;
    }
};

int find_root(int i, vector<int>& parent) {
    if (parent[i] == i)
        return i;
    return parent[i] = find_root(parent[i], parent);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    long long p, q;
    if (!(cin >> n >> m >> p >> q)) return 0;

    vector<int> parent(n + 1);
    vector<long long> comp_size(n + 1, 1);
    vector<long long> comp_weight(n + 1, 0);
    vector<int> representative(n + 1);

    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
        representative[i] = i;
    }

    int components = n;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        int root_u = find_root(u, parent);
        int root_v = find_root(v, parent);

        if (root_u != root_v) {
            parent[root_v] = root_u;
            comp_size[root_u] += comp_size[root_v];
            comp_weight[root_u] += comp_weight[root_v] + 1;
            components--;
        } else {
            comp_weight[root_u]++;
        }
    }

    // Feasibility checks
    if (q > components || p < components - q || (q == 1 && components > 1 && p < components - 1)) {
        cout << "NO\n";
        return 0;
    }

    set<Component> s;
    for (int i = 1; i <= n; ++i) {
        if (parent[i] == i) {
            s.insert({comp_weight[i], comp_size[i], i});
        }
    }

    vector<pair<int, int>> added_edges;

    // Merge components until we reach q components (or 1 if q == 1 and we need to use extra edges)
    while (components > q || (components == 1 && p > added_edges.size() && s.size() > 0)) {
        if (s.size() < 2) break;

        auto c1 = *s.begin();
        s.erase(s.begin());
        auto c2 = *s.begin();
        s.erase(s.begin());

        int u = c1.root;
        int v = c2.root;

        added_edges.push_back({u, v});

        long long new_weight = min(INF, c1.weight_sum + c2.weight_sum + 1);
        long long new_size = c1.size + c2.size;

        parent[v] = u;
        comp_weight[u] = new_weight;
        comp_size[u] = new_size;

        s.insert({new_weight, new_size, u});
        components--;

        if (added_edges.size() == p) break;
    }

    // If we still need to add more edges to reach p, add them within the largest component
    if (added_edges.size() < p) {
        auto largest_comp = *s.begin();
        int root = largest_comp.root;
        
        // Find two nodes in this component
        int u = root, v = -1;
        for (int i = 1; i <= n; ++i) {
            if (find_root(i, parent) == root && i != root) {
                v = i;
                break;
            }
        }
        if (v == -1) v = root; // fallback if single node component

        while (added_edges.size() < p) {
            added_edges.push_back({u, v});
        }
    }

    if (components != q) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (auto& edge : added_edges) {
            cout << edge.first << " " << edge.second << "\n";
        }
    }

    return 0;
}