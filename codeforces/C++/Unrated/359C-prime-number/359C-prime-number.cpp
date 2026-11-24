#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll x;
    if (!(cin >> n >> x)) return 0;

    vector<ll> a(n);
    ll sum_a = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum_a += a[i];
    }

    // Map to store frequencies of each exponent of x
    map<ll, ll> counts;
    for (int i = 0; i < n; ++i) {
        counts[sum_a - a[i]]++;
    }

    // Propagate carries upward (base x addition)
    auto it = counts.begin();
    while (it != counts.end()) {
        ll exp = it->first;
        ll count = it->second;

        if (count % x == 0) {
            counts[exp + 1] += count / x;
            it = counts.erase(it);
        } else {
            break;
        }
    }

    // The smallest remaining exponent gives the gcd
    ll min_exp = counts.begin()->first;
    ll ans = power(x, min(min_exp, sum_a));

    cout << ans << "\n";

    return 0;
}