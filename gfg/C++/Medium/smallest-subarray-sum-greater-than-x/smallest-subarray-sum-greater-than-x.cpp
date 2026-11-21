class Solution {
  public:
    int smallestSubWithSum(vector<int>& arr, int x) {
        int n = static_cast<int>(arr.size());
        long long currSum = 0;
        int minLen = n + 1;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            currSum += arr[right];

            while (currSum > x) {
                minLen = min(minLen, right - left + 1);
                currSum -= arr[left];
                ++left;
            }
        }

        return (minLen > n) ? 0 : minLen;
    }
};