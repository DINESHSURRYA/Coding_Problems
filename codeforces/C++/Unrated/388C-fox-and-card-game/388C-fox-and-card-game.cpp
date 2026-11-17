#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    int sum1 = 0, sum2 = 0;
    vector<int> middle_cards;

    for (int i = 0; i < n; ++i) {
        int s;
        cin >> s;
        vector<int> pile(s);
        for (int j = 0; j < s; ++j) {
            cin >> pile[j];
        }

        // The first half of the pile always goes to Ciel if both play greedily
        int half = s / 2;
        for (int j = 0; j < half; ++j) {
            sum1 += pile[j];
        }
        for (int j = half; j < s; ++j) {
            sum2 += pile[j];
        }

        // If the pile has an odd number of elements, the middle element is contested
        if (s % 2 != 0) {
            // Adjust the sums since the middle element was initially added to sum2 by the simple division above
            sum2 -= pile[half];
            middle_cards.push_back(pile[half]);
        }
    }

    // Sort middle cards in descending order to distribute greedily between the two players
    sort(middle_cards.rbegin(), middle_cards.rend());

    for (size_t i = 0; i < middle_cards.size(); ++i) {
        if (i % 2 == 0) {
            sum1 += middle_cards[i];
        } else {
            sum2 += middle_cards[i];
        }
    }

    cout << sum1 << " " << sum2 << "\n";

    return 0;
}