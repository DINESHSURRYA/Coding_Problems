
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    ll m;
    cin >> n >> k >> m;

    vector<ll> dp(k, 0), ndp(k, 0);

    // Empty suffix
    dp[0] = 1;

    ll ans = 0;
    ll powK = 1;

    // Number of possible prefixes
    vector<ll> pref(n + 1, 1);

    pref[0] = 1;

    ll p10 = 1;

    for (int i = 1; i <= n; i++) {
        pref[i] = (9LL * p10) % m;
        p10 = (p10 * 10) % m;
    }

    // Construct suffixes from right to left
    for (int len = 1; len <= n; len++) {

        fill(ndp.begin(), ndp.end(), 0);

        ll ways = 0;

        for (int r = 0; r < k; r++) {

            if (dp[r] == 0)
                continue;

            for (int digit = 0; digit <= 9; digit++) {

                int nr = (digit * powK + r) % k;

                if (nr == 0 && digit != 0) {
                    // Found a valid suffix
                    ways = (ways + dp[r]) % m;
                }
                else {
                    // Continue constructing the suffix
                    ndp[nr] = (ndp[nr] + dp[r]) % m;
                }
            }
        }

        // Add all possible prefixes
        ans = (ans + ways * pref[n - len]) % m;

        dp.swap(ndp);

        powK = (powK * 10) % k;
    }

    cout << ans << '\n';

    return 0;
}
