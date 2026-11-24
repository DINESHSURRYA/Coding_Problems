#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100005;
int BLOCK_SIZE;

struct Query {
    int l, r, id;
    bool operator<(const Query& other) const {
        int block_a = l / BLOCK_SIZE;
        int block_b = other.l / BLOCK_SIZE;
        if (block_a != block_b) return block_a < block_b;
        return (block_a & 1) ? (r < other.r) : (r > other.r);
    }
};

int a[MAXN];
int cnt[MAXN];
int ans = 0;
int answers[MAXN];

inline void add(int x) {
    if (x >= MAXN) return;
    if (cnt[x] == x) ans--;
    cnt[x]++;
    if (cnt[x] == x) ans++;
}

inline void remove(int x) {
    if (x >= MAXN) return;
    if (cnt[x] == x) ans--;
    cnt[x]--;
    if (cnt[x] == x) ans++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    BLOCK_SIZE = sqrt(n);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<Query> queries(m);
    for (int i = 0; i < m; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end());

    int current_l = 1, current_r = 0;

    for (int i = 0; i < m; ++i) {
        int L = queries[i].l;
        int R = queries[i].r;

        while (current_l > L) {
            current_l--;
            add(a[current_l]);
        }
        while (current_r < R) {
            current_r++;
            add(a[current_r]);
        }
        while (current_l < L) {
            remove(a[current_l]);
            current_l++;
        }
        while (current_r > R) {
            remove(a[current_r]);
            current_r--;
        }

        answers[queries[i].id] = ans;
    }

    for (int i = 0; i < m; ++i) {
        cout << answers[i] << "\n";
    }

    return 0;
}