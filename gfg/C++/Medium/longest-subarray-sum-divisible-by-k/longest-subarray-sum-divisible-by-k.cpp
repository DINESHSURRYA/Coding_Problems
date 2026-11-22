class Solution {
  public:
    int longestSubarrayDivK(vector<int>& arr, int k) {
        unordered_map<int, int> firstSeen;
        firstSeen[0] = -1;

        long long prefixSum = 0;
        int maxLen = 0;

        for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
            prefixSum += arr[i];
            int rem = static_cast<int>(((prefixSum % k) + k) % k);

            if (firstSeen.find(rem) != firstSeen.end()) {
                maxLen = max(maxLen, i - firstSeen[rem]);
            } else {
                firstSeen[rem] = i;
            }
        }

        return maxLen;
    }
};