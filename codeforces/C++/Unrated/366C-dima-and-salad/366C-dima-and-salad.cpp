#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int OFFSET = 100005;
const int INF = 1e9;
int dp[2 * OFFSET + 5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    // Initialize DP table with -1 (meaning unreachable)
    for (int i = 0; i <= 2 * OFFSET; ++i) {
        dp[i] = -INF;
    }

    // Base case: 0 sum difference gives 0 taste sum
    dp[OFFSET] = 0;

    for (int i = 0; i < n; ++i) {
        int diff = a[i] - k * b[i];
        
        // Traverse backwards to use each item at most once (0/1 Knapsack style)
        if (diff > 0) {
            for (int j = 2 * OFFSET; j >= diff; --j) {
                if (dp[j - diff] != -INF) {
                    dp[j] = max(dp[j], dp[j - diff] + a[i]);
                }
            }
        } else {
            for (int j = 0; j <= 2 * OFFSET + diff; ++j) {
                if (dp[j - diff] != -INF) {
                    dp[j] = max(dp[j], dp[j - diff] + a[i]);
                }
            }
        }
    }

    // We want the net difference to be 0 (which is at OFFSET)
    int ans = dp[OFFSET];

    // If ans <= 0, it means no valid non-empty subset achieved the exact ratio
    if (ans <= 0) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}