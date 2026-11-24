#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

// Structure to represent a line: y = m * x + c
struct Line {
    ll m, c;
    ll eval(ll x) {
        return m * x + c;
    }
};

// Check if line l3 is redundant given l1 and l2
bool bad(Line l1, Line l2, Line l3) {
    // Intersection of l1 and l3 vs l1 and l2
    return (double)(l3.c - l1.c) / (l1.m - l3.m) <= (double)(l2.c - l1.c) / (l1.m - l2.m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    vector<ll> dp(n, 0);
    vector<Line> hull;
    
    // Function to add a line to the convex hull
    auto add_line = [&](ll m, ll c) {
        Line l = {m, c};
        while (hull.size() >= 2 && bad(hull[hull.size() - 2], hull.back(), l)) {
            hull.pop_back();
        }
        hull.push_back(l);
    };

    // Pointer to query the best line efficiently since queries are monotonic
    int ptr = 0;
    auto query = [&](ll x) {
        if (ptr >= hull.size()) ptr = hull.size() - 1;
        while (ptr + 1 < hull.size() && hull[ptr + 1].eval(x) <= hull[ptr].eval(x)) {
            ptr++;
        }
        return hull[ptr].eval(x);
    };

    // Base case
    dp[0] = 0;
    add_line(b[0], dp[0]);

    for (int i = 1; i < n; ++i) {
        dp[i] = query(a[i]);
        add_line(b[i], dp[i]);
    }

    cout << dp[n - 1] << "\n";

    return 0;
}