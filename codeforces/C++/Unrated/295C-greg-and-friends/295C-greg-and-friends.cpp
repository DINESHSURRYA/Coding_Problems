#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

long long C[55][55];

void precompute() {
    for (int i = 0; i <= 50; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
}

struct State {
    int c50, c100, pos;
};

int dist[51][51][2];
long long ways[51][51][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int n, k;
    if (!(cin >> n >> k)) return 0;

    int total50 = 0, total100 = 0;
    for (int i = 0; i < n; ++i) {
        int weight;
        cin >> weight;
        if (weight == 50) total50++;
        else total100++;
    }

    int max_people = k / 50;

    memset(dist, -1, sizeof(dist));

    queue<State> q;
    q.push({total50, total100, 0});
    dist[total50][total100][0] = 0;
    ways[total50][total100][0] = 1;

    while (!q.empty()) {
        State u = q.front();
        q.pop();

        int c50 = u.c50;
        int c100 = u.c100;
        int pos = u.pos;

        // Determine available people to choose from based on current boat position
        int avail50 = (pos == 0) ? c50 : (total50 - c50);
        int avail100 = (pos == 0) ? c100 : (total100 - c100);

        // Try all combinations of moving people
        for (int i = 0; i <= min(avail50, max_people); ++i) {
            int rem_capacity = max_people - i;
            for (int j = 0; j <= min(avail100, rem_capacity / 2); ++j) {
                if (i == 0 && j == 0) continue;

                int next_c50, next_c100, next_pos;
                if (pos == 0) {
                    next_c50 = c50 - i;
                    next_c100 = c100 - j;
                    next_pos = 1;
                } else {
                    next_c50 = c50 + i;
                    next_c100 = c100 + j;
                    next_pos = 0;
                }

                long long ways_comb = (1LL * C[avail50][i] * C[avail100][j]) % MOD;

                if (dist[next_c50][next_c100][next_pos] == -1) {
                    dist[next_c50][next_c100][next_pos] = dist[c50][c100][pos] + 1;
                    ways[next_c50][next_c100][next_pos] = (ways[c50][c100][pos] * ways_comb) % MOD;
                    q.push({next_c50, next_c100, next_pos});
                } else if (dist[next_c50][next_c100][next_pos] == dist[c50][c100][pos] + 1) {
                    ways[next_c50][next_c100][next_pos] = (ways[next_c50][next_c100][next_pos] + ways[c50][c100][pos] * ways_comb) % MOD;
                }
            }
        }
    }

    if (dist[0][0][1] == -1) {
        cout << -1 << "\n" << 0 << "\n";
    } else {
        cout << dist[0][0][1] << "\n";
        cout << ways[0][0][1] << "\n";
    }

    return 0;
}