/*
 * @lc app=leetcode id=538 lang=cpp
 *
 * [538] Convert BST to Greater Tree
 */
#include<stack>
#include<iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        int sum = 0;
        TreeNode* node = root;
        std::stack<TreeNode*> Tstack; 
        while(!Tstack.empty() || node != nullptr){
            while(node != nullptr){
                Tstack.push(node);
                node = node->right;
            }
            node = Tstack.top();
            sum += node->val;
            node->val = sum;
            node = node->left;
            Tstack.pop();
        }
        return root;
    }
};

/*
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        if(root != nullptr){
        convertBST(root->right);
        sum += root->val;
        root->val = sum;
        convertBST(root->left);
        }
        else return nullptr;
        return root;
    }
private: 
    int sum=0;
};
 */


int main(){
    auto root = new TreeNode(5);
    auto node_1 = new TreeNode(2);
    auto node_2 = new TreeNode(13);
    root->left = node_1;
    root->right = node_2;
    root = Solution().convertBST(root);
    std::cout<<root->val<<std::endl;
    return 0;
}


