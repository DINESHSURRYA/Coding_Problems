
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, d;
    cin >> n >> m >> d;

    const ll NEG = -(1LL << 60);

    vector<ll> dp(n + 1, 0);
    vector<ll> ndp(n + 1, NEG);

    int prevTime = 1;

    for (int i = 0; i < m; i++) {
        int a, t;
        ll b;
        cin >> a >> b >> t;

        ll reach = (i == 0 ? 0LL : min(1LL * n, 1LL * d * (t - prevTime)));

        deque<int> dq;
        int right = 0;

        for (int x = 1; x <= n; x++) {

            int L = max(1LL, x - reach);
            int R = min(1LL * n, x + reach);

            // Add newly reachable positions
            while (right < R) {
                right++;

                while (!dq.empty() && dp[dq.back()] <= dp[right]) {
                    dq.pop_back();
                }

                dq.push_back(right);
            }

            // Remove positions outside the window
            while (!dq.empty() && dq.front() < L) {
                dq.pop_front();
            }

            ndp[x] = dp[dq.front()] + b - abs(a - x);
        }

        dp.swap(ndp);
        fill(ndp.begin(), ndp.end(), NEG);

        prevTime = t;
    }

    cout << *max_element(dp.begin() + 1, dp.end()) << '\n';

    return 0;
}
