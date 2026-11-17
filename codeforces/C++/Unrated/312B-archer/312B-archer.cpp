#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    double a, b, c, d;
    if (cin >> a >> b >> c >> d) {
        double prob_r = a / b;
        double miss_r = 1.0 - prob_r;
        double miss_z = 1.0 - (c / d);

        // Infinite geometric series sum: a / (1 - r)
        double ans = prob_r / (1.0 - (miss_r * miss_z));

        cout << fixed << setprecision(12) << ans << "\n";
    }

    return 0;
}