/*
 * @lc app=leetcode id=771 lang=cpp
 *
 * [771] Jewels and Stones
 */
#include<string>
#include<unordered_set>
using namespace std;
class Solution {
public:
    int numJewelsInStones(string J, string S) {
        unordered_set<char> jewels;
        for(char c:J)
            jewels.insert(c);
        int res = 0;
        for(char c:S)
            if(jewels.find(c)!=jewels.end())
                res ++;
        return res;
    }
};

