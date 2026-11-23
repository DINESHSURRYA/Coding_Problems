class Solution {
  public:
    char posInfinite(string &s, int pos) {
        long long n = s.size();
        long long p = pos;

        // Track string lengths after each step until length >= pos
        vector<long long> lengths;
        lengths.push_back(n);

        long long step = 1;
        while (lengths.back() < p) {
            long long nextLen = 2 * lengths.back() + step;
            lengths.push_back(nextLen);
            step++;
        }

        // Work backward from the step that covers position p
        for (int i = static_cast<int>(lengths.size()) - 1; i >= 1; --i) {
            long long prevLen = lengths[i - 1];
            long long dollars = i; // In step i, i '$' characters are inserted

            if (p <= prevLen) {
                // Position lies in the first half (unchanged)
                continue;
            } else if (p <= prevLen + dollars) {
                // Position lies in the middle '$' segment
                return '$';
            } else {
                // Position lies in reverse(prev_string)
                // Index 'offset' (1-based) in reverse(prev_string) maps directly to
                // index (prevLen - offset + 1) in prev_string
                long long offset = p - (prevLen + dollars);
                p = prevLen - offset + 1;
            }
        }

        return s[p - 1];
    }
};