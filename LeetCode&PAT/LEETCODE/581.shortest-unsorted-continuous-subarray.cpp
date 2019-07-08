/*
 * @lc app=leetcode id=581 lang=cpp
 *
 * [581] Shortest Unsorted Continuous Subarray
 */
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        vector<int> stack;
        int l=nums.size(),r=0;
        for(int i=0;i<nums.size();++i){
            while(!stack.empty() && nums[stack.back()]>nums[i]){
                l = min(l,stack.back());
                stack.pop_back();
            }
            stack.push_back(i);   
        }
        stack.clear();
        for(int i=nums.size()-1;i>=0;--i){
            while(!stack.empty() && nums[stack.back()]<nums[i]){
                r = max(r,stack.back());
                stack.pop_back();
            }
            stack.push_back(i);
        }
        return r-l>0?r-l+1:0;
    }
};

