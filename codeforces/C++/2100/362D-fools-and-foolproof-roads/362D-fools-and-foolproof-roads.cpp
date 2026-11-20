#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    // max_p[i] = max probability among fools i..n-1
    // has_100[i] = true if at least one fool in i..n-1 has p == 100
    vector<int> max_p(n + 1, 0);
    vector<bool> has_100(n + 1, false);
    for (int i = n - 1; i >= 0; --i) {
        max_p[i] = max(max_p[i + 1], p[i]);
        has_100[i] = has_100[i + 1] || (p[i] == 100);
    }

    // State (a, b) represents the two lowest-indexed surviving fools (a < b).
    // If <= 1 fool survives, we represent it with a = n or b = n.
    // Since after k rounds, the state after the first two fools is always a contiguous suffix [b..n-1],
    // (a, b) uniquely identifies the entire set of alive fools!
    vector<vector<int>> dist(n + 2, vector<int>(n + 2, -1));
    queue<pair<int, int>> q;

    int start_a = 0;
    int start_b = (n > 1) ? 1 : n;
    dist[start_a][start_b] = 0;
    q.push({start_a, start_b});

    int ans = 0;

    while (!q.empty()) {
        auto [a, b] = q.front();
        q.pop();
        ans++;

        int d = dist[a][b];
        if (d == k || b >= n) continue;

        bool a_can_hit = (p[a] > 0);
        bool a_must_hit = (p[a] == 100);

        bool rest_can_hit = (max_p[b] > 0);
        bool rest_must_hit = has_100[b];

        // Transition 1: Both a and b die (a hits b, and someone in b..n-1 hits a)
        if (a_can_hit && rest_can_hit) {
            int na = (b + 1 < n) ? b + 1 : n;
            int nb = (b + 2 < n) ? b + 2 : n;
            if (dist[na][nb] == -1) {
                dist[na][nb] = d + 1;
                q.push({na, nb});
            }
        }

        // Transition 2: a survives, b dies (a hits b, and nobody in b..n-1 hits a)
        if (a_can_hit && !rest_must_hit) {
            int na = a;
            int nb = (b + 1 < n) ? b + 1 : n;
            if (dist[na][nb] == -1) {
                dist[na][nb] = d + 1;
                q.push({na, nb});
            }
        }

        // Transition 3: a dies, b survives (a misses b, and someone in b..n-1 hits a)
        if (!a_must_hit && rest_can_hit) {
            int na = b;
            int nb = (b + 1 < n) ? b + 1 : n;
            if (dist[na][nb] == -1) {
                dist[na][nb] = d + 1;
                q.push({na, nb});
            }
        }
        // Note: If neither dies, the state stays (a, b), which is already visited at an earlier or equal step.
    }

    cout << ans << "\n";
    return 0;
}