
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> x(n);
    for (int &v : x) cin >> v;

    int a, b;
    cin >> a >> b;

    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());

    int len = a - b;
    vector<int> dp(len + 1, INF);

    dp[0] = 0;

    for (int i = 1; i <= len; i++) {
        int v = b + i;

        dp[i] = dp[i - 1] + 1;

        for (int mod : x) {
            int r = v % mod;

            if (r == 0) continue;

            int nxt = v - r;

            if (nxt >= b) {
                dp[i] = min(dp[i], dp[nxt - b] + 1);
            }
        }
    }

    cout << dp[len] << '\n';

    return 0;
}
