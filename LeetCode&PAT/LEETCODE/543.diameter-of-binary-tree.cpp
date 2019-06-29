/*
 * @lc app=leetcode id=543 lang=cpp
 *
 * [543] Diameter of Binary Tree
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        travDepth(root);
        return res;
    }
private:
    int res = 0;
    // 辅助函数计算 某一节点 左子树深度 + 右子树深度 + 1
    int travDepth(TreeNode* root){
        if(root == nullptr) return 0;
        int leftDepth = travDepth(root->left);
        int rightDepth = travDepth(root->right);
        res = res > (leftDepth+rightDepth)?res:(leftDepth+rightDepth);
        return 1 + (leftDepth>rightDepth?leftDepth:rightDepth);
    }    
};

