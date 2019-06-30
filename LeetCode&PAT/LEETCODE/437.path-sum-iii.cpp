/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        if(root == nullptr)
            return 0;
        // 利用递归遍历所有节点
        return findPath(root,sum) 
            + pathSum(root->left,sum)
            + pathSum(root->right,sum);
    }
private:
    // 利用递归来获取值
    int findPath(TreeNode* node,int sum){
        if(node == nullptr)
            return 0;
        int res = 0;
        if(node->val == sum)
            res += 1;
        res += findPath(node->left,sum-node->val);
        res += findPath(node->right,sum-node->val);
        return res;
    }
};