/*
 * @lc app=leetcode id=121 lang=cpp
 *
 * [121] Best Time to Buy and Sell Stock
 */

#include<vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()==0)
            return 0;
        int minPrice = prices[0];
        int maxProfit = 0;
        for(int i=1;i<prices.size();++i){
            maxProfit = max(maxProfit,prices[i]-minPrice);
            minPrice = min(minPrice,prices[i]);
        }
        return maxProfit;
    }
};

