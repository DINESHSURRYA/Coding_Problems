using namespace std;

class Solution {
private:
    // Helper function to find XOR from 1 to n
    int computeXOR(int n) {
        int mod = n % 4;
        if (mod == 0) return n;
        if (mod == 1) return 1;
        if (mod == 2) return n + 1;
        return 0; // mod == 3
    }

public:
    int findXOR(int l, int r) {
        // XOR from l to r is (XOR from 1 to l-1) ^ (XOR from 1 to r)
        return computeXOR(l - 1) ^ computeXOR(r);
    }
};