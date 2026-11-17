#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXVAL = 1000005;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    int max_elem = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        max_elem = max(max_elem, a[i]);
    }

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    // exists[v] will store whether value v exists in the array
    vector<bool> exists(max_elem + 1, false);
    for (int x : a) {
        exists[x] = true;
    }

    // precompute next existing element for fast lookup
    vector<int> next_val(2 * max_elem + 2, 2 * max_elem + 2);
    int last = 2 * max_elem + 2;
    for (int i = 2 * max_elem + 1; i >= 0; --i) {
        if (i <= max_elem && exists[i]) {
            last = i;
        }
        next_val[i] = last;
    }

    int max_mod = 0;
    int unique_n = a.size();

    for (int i = 0; i < unique_n; ++i) {
        int x = a[i];
        // If x is 1, the maximum possible modulo is 0, we can skip
        if (x == 1) continue;

        for (int mult = 2 * x; mult <= max_elem + x; mult += x) {
            // Find largest element strictly less than mult
            int idx = next_val[mult];
            if (idx > mult - 1) {
                // Look back to find the largest element < mult
                // Using binary search on sorted array 'a'
                auto it = lower_bound(a.begin(), a.end(), mult);
                if (it != a.begin()) {
                    --it;
                    max_mod = max(max_mod, (*it) % x);
                }
            } else {
                // idx points to the largest element <= mult-1
                auto it = lower_bound(a.begin(), a.end(), mult);
                if (it != a.begin()) {
                    --it;
                    max_mod = max(max_mod, (*it) % x);
                }
            }
        }
    }

    cout << max_mod << "\n";

    return 0;
}