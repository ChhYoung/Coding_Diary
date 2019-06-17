/*
 * @lc app=leetcode id=136 lang=cpp
 *
 * [136] Single Number
 */
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for(auto &i:nums){
            res ^= i;
        }
        return res;
    }
};

