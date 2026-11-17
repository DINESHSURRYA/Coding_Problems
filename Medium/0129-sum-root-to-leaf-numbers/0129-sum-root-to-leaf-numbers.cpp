/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int sumNumbers(TreeNode* root) {
     int sum = 0;
     return ans(root, sum);   
    }

    int ans(TreeNode* root, int sum) {
        if (root == 0) {return 0;}

        sum = (sum * 10) + root->val;

        if (root->left == 0 && root->right == 0) {
            return sum;
        }

        int l = ans(root->left, sum), r = ans(root->right, sum);

        return l + r;
    }
};