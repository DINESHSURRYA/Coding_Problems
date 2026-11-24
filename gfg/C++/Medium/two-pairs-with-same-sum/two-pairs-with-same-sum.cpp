class Solution {
  public:
    vector<int> findPairs(vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        unordered_map<int, pair<int, int>> firstPair;
        vector<int> best = {n, n, n, n};
        bool found = false;

        // Iterate i and j in increasing order so (i, j) is naturally lexicographically smallest
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int sum = arr[i] + arr[j];
                auto it = firstPair.find(sum);

                if (it != firstPair.end()) {
                    int a = it->second.first;
                    int b = it->second.second;
                    int c = i;
                    int d = j;

                    // All four indices a, b, c, d must be distinct
                    if (a != c && a != d && b != c && b != d) {
                        // Ensure (a, b) is lexicographically smaller than (c, d)
                        if (make_pair(a, b) > make_pair(c, d)) {
                            swap(a, c);
                            swap(b, d);
                        }

                        vector<int> cand = {a, b, c, d};
                        if (!found || cand < best) {
                            best = cand;
                            found = true;
                        }
                    }
                } else {
                    // Since we iterate (i, j) in increasing lexicographical order,
                    // the first pair seen for a given sum is already optimal for that sum.
                    firstPair[sum] = {i, j};
                }
            }
        }

        return found ? best : vector<int>{-1, -1, -1, -1};
    }
};