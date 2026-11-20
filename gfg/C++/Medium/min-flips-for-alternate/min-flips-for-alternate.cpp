class Solution {
  public:
    int minFlips(string &s) {
        int n = s.size();
        int flipsStartingWithZero = 0;

        for (int i = 0; i < n; i++) {
            char expected = (i % 2 == 0) ? '0' : '1';
            if (s[i] != expected) {
                flipsStartingWithZero++;
            }
        }

        // Flips needed for "101010..." is simply n - flipsStartingWithZero
        return min(flipsStartingWithZero, n - flipsStartingWithZero);
    }
};