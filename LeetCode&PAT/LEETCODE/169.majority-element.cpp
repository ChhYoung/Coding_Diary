/*
 * @lc app=leetcode id=169 lang=cpp
 *
 * [169] Majority Element
 */
/* 
// solution 1: use sort
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        return nums[nums.size()/2];
    }
};
*/

// solution 2 : use hash map
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int,int> res;
        for(int &num:nums)
            res[num]++;
        for(pair<int,int> i:res){
            if(i.second>nums.size()/2)
                return i.first;
        }
    }
};

