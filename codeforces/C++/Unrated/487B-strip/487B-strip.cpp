
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long k;
    cin >> k;

    vector<string> g(1000, string(1000, 'N'));

    int n = 2; // vertex 1 = source, vertex 2 = destination

    auto addEdge = [&](int u, int v) {
        g[u][v] = 'Y';
        g[v][u] = 'Y';
    };

    int mx = 0;

    for (int i = 0; i < 30; i++) {
        if (k & (1LL << i)) {
            mx = i;
        }
    }

    int L = mx + 1;

    // Construct one independent gadget for every set bit
    for (int i = 0; i <= mx; i++) {

        if (!(k & (1LL << i)))
            continue;

        int padding = L - i - 1;
        int cur = 0;

        // Add a chain to make all paths equal in length
        for (int j = 0; j < padding; j++) {
            int v = n++;
            addEdge(cur, v);
            cur = v;
        }

        if (i == 0) {
            addEdge(cur, 1);
            continue;
        }

        // Create the first layer of two vertices
        int a = n++;
        int b = n++;

        addEdge(cur, a);
        addEdge(cur, b);

        // Create i layers, each containing two vertices
        for (int j = 1; j < i; j++) {
            int c = n++;
            int d = n++;

            addEdge(a, c);
            addEdge(a, d);
            addEdge(b, c);
            addEdge(b, d);

            a = c;
            b = d;
        }

        // Connect the last layer to destination
        addEdge(a, 1);
        addEdge(b, 1);
    }

    cout << n << '\n';

    for (int i = 0; i < n; i++) {
        cout << g[i].substr(0, n) << '\n';
    }

    return 0;
}
