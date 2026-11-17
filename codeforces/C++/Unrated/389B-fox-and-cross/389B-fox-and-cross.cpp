#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '#') {
                // (i, j) must be the top end of the cross
                if (i + 2 < n && j - 1 >= 0 && j + 1 < n &&
                    grid[i + 1][j] == '#' &&
                    grid[i + 1][j - 1] == '#' &&
                    grid[i + 1][j + 1] == '#' &&
                    grid[i + 2][j] == '#') {
                    
                    // Mark cross as used
                    grid[i][j] = '.';
                    grid[i + 1][j] = '.';
                    grid[i + 1][j - 1] = '.';
                    grid[i + 1][j + 1] = '.';
                    grid[i + 2][j] = '.';
                } else {
                    cout << "NO\n";
                    return 0;
                }
            }
        }
    }

    cout << "YES\n";
    return 0;
}