#include <iostream>
#include <vector>

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

    // Find all divisors d of n
    vector<int> divisors;
    for (int d = 1; d * d <= n; ++d) {
        if (n % d == 0) {
            // Check if step size d gives at least 3 vertices
            if (n / d >= 3) {
                divisors.push_back(d);
            }
            int other_d = n / d;
            // Check the paired divisor
            if (other_d != d && n / other_d >= 3) {
                divisors.push_back(other_d);
            }
        }
    }

    // Test each valid step size d
    for (int d : divisors) {
        for (int s = 0; s < d; ++s) {
            bool all_good = true;
            for (int pos = s; pos < n; pos += d) {
                if (a[pos] == 0) {
                    all_good = false;
                    break;
                }
            }
            if (all_good) {
                cout << "YES\n";
                return 0;
            }
        }
    }

    cout << "NO\n";

    return 0;
}