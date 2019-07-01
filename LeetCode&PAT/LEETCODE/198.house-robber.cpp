/*
 * @lc app=leetcode id=198 lang=cpp
 *
 * [198] House Robber
 */
class Solution{
public:
    int rob(vector<int>& nums){
        int n = nums.size();
        if(n == 0)
            return 0;
        // 记录前两个位置的最大值
        int preMax = 0, curMax = 0;
        for(int i = n-1 ; i>=0; --i){
            int temp = curMax;
            curMax = max(curMax,nums[i] + preMax);
            preMax = temp;
        }
        return curMax;
    }
};

