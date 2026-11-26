
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> x(n);

    for (auto &v : x) cin >> v;

    long long a, b;
    cin >> a >> b;

    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());

    int ans = 0;

    while (a > b) {
        long long best = 1;
        int sz = x.size();

        for (int i = sz - 1; i >= 0; i--) {
            long long r = a % x[i];

            if (a - r < b) {
                swap(x[i], x[sz - 1]);
                sz--;
            } 
            else {
                best = max(best, r);
            }
        }

        x.resize(sz);

        a -= best;
        ans++;
    }

    cout << ans << '\n';

    return 0;
}
