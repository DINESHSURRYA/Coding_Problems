#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    int c4, c7, c47, c74;
};

int n, m;
string s;
vector<Node> tree;
vector<bool> lazy;

Node merge(const Node& a, const Node& b) {
    Node res;
    res.c4 = a.c4 + b.c4;
    res.c7 = a.c7 + b.c7;
    res.c47 = max(a.c4 + b.c47, a.c47 + b.c7);
    res.c74 = max(a.c7 + b.c74, a.c74 + b.c4);
    return res;
}

void apply_flip(int node) {
    swap(tree[node].c4, tree[node].c7);
    swap(tree[node].c47, tree[node].c74);
    lazy[node] = !lazy[node];
}

void push(int node) {
    if (lazy[node]) {
        apply_flip(2 * node);
        apply_flip(2 * node + 1);
        lazy[node] = false;
    }
}

void build(int node, int start, int end) {
    if (start == end) {
        if (s[start] == '4') {
            tree[node] = {1, 0, 1, 1};
        } else {
            tree[node] = {0, 1, 1, 1};
        }
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return;
    }
    if (l <= start && end <= r) {
        apply_flip(node);
        return;
    }
    push(node);
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r);
    update(2 * node + 1, mid + 1, end, l, r);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;
    cin >> s;

    tree.resize(4 * n);
    lazy.assign(4 * n, false);

    build(1, 0, n - 1);

    for (int i = 0; i < m; ++i) {
        string type;
        cin >> type;
        if (type == "count") {
            cout << tree[1].c47 << "\n";
        } else {
            int l, r;
            cin >> l >> r;
            update(1, 0, n - 1, l - 1, r - 1);
        }
    }

    return 0;
}