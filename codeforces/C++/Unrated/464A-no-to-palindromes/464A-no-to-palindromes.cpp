#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, p;
    if (!(cin >> n >> p)) return 0;

    string s;
    cin >> s;

    char max_char = 'a' + p - 1;

    // Try incrementing from right to left
    for (int i = n - 1; i >= 0; --i) {
        for (char c = s[i] + 1; c <= max_char; ++c) {
            // Check condition against two previous characters
            if (i >= 1 && c == s[i - 1]) continue;
            if (i >= 2 && c == s[i - 2]) continue;

            // Found a valid character at position i
            s[i] = c;

            // Fill all subsequent positions greedily with the smallest valid character
            bool possible = true;
            for (int j = i + 1; j < n; ++j) {
                bool found = false;
                for (char fill_c = 'a'; fill_c <= max_char; ++fill_c) {
                    if (j >= 1 && fill_c == s[j - 1]) continue;
                    if (j >= 2 && fill_c == s[j - 2]) continue;

                    s[j] = fill_c;
                    found = true;
                    break;
                }
                if (!found) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                cout << s << "\n";
                return 0;
            }
        }
    }

    cout << "NO\n";

    return 0;
}