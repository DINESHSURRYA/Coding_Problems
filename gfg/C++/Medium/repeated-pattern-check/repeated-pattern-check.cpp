#include <string>

using namespace std;

class Solution {
public:
    bool findPattern(string &s) {
        int n = s.length();
        // The length must be even because each 'x' block must have a matching 'y' block
        if (n % 2 != 0) return false;
        
        int count_x = 0, count_y = 0;
        for (char c : s) {
            if (c == 'x') count_x++;
            else if (c == 'y') count_y++;
        }
        
        // Total count of x's must equal total count of y's
        if (count_x != count_y) return false;
        
        // Check if characters alternate or group correctly according to x^n y^n
        // A simple recursive or iterative verification of blocks:
        int i = 0;
        while (i < n) {
            int x_count = 0;
            while (i < n && s[i] == 'x') {
                x_count++;
                i++;
            }
            
            int y_count = 0;
            while (i < n && s[i] == 'y') {
                y_count++;
                i++;
            }
            
            if (x_count != y_count || x_count == 0) {
                return false;
            }
        }
        
        return true;
    }
};