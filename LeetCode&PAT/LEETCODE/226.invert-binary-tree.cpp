/*
 * @lc app=leetcode id=226 lang=cpp
 *
 * [226] Invert Binary Tree
 */

 // Definition for a binary tree node.
#include<iostream>
#include<vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return nullptr;
        vector<TreeNode*> stack;
        stack.push_back(root);
        while(!stack.empty()){
            auto temp = stack.back();
            stack.pop_back();
            swap(temp->left,temp->right);
            if(temp->left) stack.push_back(temp->left);
            if(temp->right) stack.push_back(temp->right);
        }
        return root;
    }
};

