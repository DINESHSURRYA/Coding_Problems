class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int maxi = 0;
        const long long mod = 1e9 + 7;

        for(int i = 0; i < n; i++){
            long long pro = 1;
            int f = nums[i];
            long long s = nums[i];

            for(int j = i; j < n; j++){
                pro = (pro * nums[j]) % mod;
                f = gcd(f, nums[j]);
                s = (s / gcd((long long)s, nums[j]) * nums[j]) % mod;
                if(pro == (s * f) % mod){
                    maxi = max(maxi, j - i + 1);
                }
            }
        }
        return maxi;
    }
};