/*
 * @lc app=leetcode id=283 lang=cpp
 *
 * [283] Move Zeroes
 */
#include<vector>
using namespace std;
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int k=0;
        for(int i=0;i<nums.size();++i)
            if(nums[i])
                swap(nums[k++],nums[i]);
    }
};

