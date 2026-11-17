#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> jiro_atk;
    vector<int> jiro_def;

    for (int i = 0; i < n; ++i) {
        string pos;
        int val;
        cin >> pos >> val;
        if (pos == "ATK") {
            jiro_atk.push_back(val);
        } else {
            jiro_def.push_back(val);
        }
    }

    vector<int> ciel(m);
    for (int i = 0; i < m; ++i) {
        cin >> ciel[i];
    }

    sort(jiro_atk.begin(), jiro_atk.end());
    sort(jiro_def.begin(), jiro_def.end());
    sort(ciel.begin(), ciel.end());

    int ans = 0;

    // Option 1: Destroy only k of Jiro's ATK cards (no direct attacks)
    int max_k = min((int)jiro_atk.size(), m);
    for (int k = 1; k <= max_k; ++k) {
        bool ok = true;
        int current_damage = 0;
        for (int i = 0; i < k; ++i) {
            int ciel_card = ciel[m - k + i];
            int jiro_card = jiro_atk[i];
            if (ciel_card < jiro_card) {
                ok = false;
                break;
            }
            current_damage += (ciel_card - jiro_card);
        }
        if (ok) {
            ans = max(ans, current_damage);
        }
    }

    // Option 2: Destroy ALL of Jiro's cards and deal direct damage
    if (m > n) {
        vector<bool> used(m, false);
        bool possible = true;

        // 1. Defeat all DEF cards with smallest strictly greater card
        for (int d : jiro_def) {
            int pick = -1;
            for (int i = 0; i < m; ++i) {
                if (!used[i] && ciel[i] > d) {
                    pick = i;
                    break;
                }
            }
            if (pick == -1) {
                possible = false;
                break;
            }
            used[pick] = true;
        }

        // 2. Defeat all ATK cards with smallest >= card
        int damage_opt2 = 0;
        if (possible) {
            for (int a : jiro_atk) {
                int pick = -1;
                for (int i = 0; i < m; ++i) {
                    if (!used[i] && ciel[i] >= a) {
                        pick = i;
                        break;
                    }
                }
                if (pick == -1) {
                    possible = false;
                    break;
                }
                used[pick] = true;
                damage_opt2 += (ciel[pick] - a);
            }
        }

        // 3. Direct attack with all remaining unused cards
        if (possible) {
            for (int i = 0; i < m; ++i) {
                if (!used[i]) {
                    damage_opt2 += ciel[i];
                }
            }
            ans = max(ans, damage_opt2);
        }
    }

    cout << ans << "\n";

    return 0;
}