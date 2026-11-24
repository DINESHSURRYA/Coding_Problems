
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long k;
    cin >> k;

    int m = 0;
    for (int i = 0; i < 31; i++) {
        if (k & (1LL << i)) {
            m = i;
        }
    }

    int n = 2;

    // Vertex 0 = source, vertex 1 = destination
    vector<int> chain(m + 1);
    vector<int> L(m + 1), R(m + 1);

    chain[0] = 0;

    for (int i = 1; i <= m; i++)
        chain[i] = n++;

    for (int i = 0; i <= m; i++) {
        L[i] = n++;
        R[i] = n++;
    }

    vector<string> g(n, string(n, 'N'));

    auto addEdge = [&](int u, int v) {
        g[u][v] = 'Y';
        g[v][u] = 'Y';
    };

    // Build the common chain
    for (int i = 0; i < m; i++) {
        addEdge(chain[i], chain[i + 1]);
    }

    // Build layered graph
    for (int i = 0; i < m; i++) {
        addEdge(L[i], L[i + 1]);
        addEdge(L[i], R[i + 1]);
        addEdge(R[i], L[i + 1]);
        addEdge(R[i], R[i + 1]);
    }

    // Add connections for every set bit
    for (int i = 0; i <= m; i++) {
        if (k & (1LL << i)) {
            int j = m - i;
            addEdge(chain[j], L[j]);
        }
    }

    // Connect the last layer to destination
    addEdge(L[m], 1);
    addEdge(R[m], 1);

    cout << n << '\n';

    for (int i = 0; i < n; i++) {
        cout << g[i] << '\n';
    }

    return 0;
}
