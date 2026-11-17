#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> dp1(n), dp2(n);
    vector<int> lis_tails;

    // Compute dp1[i]: length of LIS ending at i
    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(lis_tails.begin(), lis_tails.end(), a[i]);
        if (it == lis_tails.end()) {
            lis_tails.push_back(a[i]);
            dp1[i] = lis_tails.size();
        } else {
            *it = a[i];
            dp1[i] = it - lis_tails.begin() + 1;
        }
    }

    int max_lis = lis_tails.size();
    lis_tails.clear();

    // Compute dp2[i]: length of LIS starting at i (by going backwards)
    for (int i = n - 1; i >= 0; --i) {
        auto it = lower_bound(lis_tails.begin(), lis_tails.end(), -a[i]);
        if (it == lis_tails.end()) {
            lis_tails.push_back(-a[i]);
            dp2[i] = lis_tails.size();
        } else {
            *it = -a[i];
            dp2[i] = it - lis_tails.begin() + 1;
        }
    }

    // Count frequencies of each dp1 position value to determine Type 2 vs Type 3
    vector<int> count_pos(max_lis + 1, 0);
    vector<int> ans(n, 1); // Default to Type 1

    for (int i = 0; i < n; ++i) {
        if (dp1[i] + dp2[i] - 1 == max_lis) {
            ans[i] = 2; // Tentatively Type 2
            count_pos[dp1[i]]++;
        } else {
            ans[i] = 1; // Type 1
        }
    }

    // If an element's dp1 position count is 1, it must be part of ALL LIS -> Type 3
    for (int i = 0; i < n; ++i) {
        if (ans[i] == 2 && count_pos[dp1[i]] == 1) {
            ans[i] = 3;
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i];
    }
    cout << "\n";

    return 0;
}