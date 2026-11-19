#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void sortIt(vector<int>& arr) {
        for (int& x : arr) {
            if (x % 2 != 0) {
                x = -x; // Odd numbers become negative for descending order
            }
        }

        sort(arr.begin(), arr.end());

        for (int& x : arr) {
            if (x < 0) {
                x = -x; // Restore original odd values
            }
        }
    }
};