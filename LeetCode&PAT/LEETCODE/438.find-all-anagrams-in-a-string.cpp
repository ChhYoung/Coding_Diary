/*
 * @lc app=leetcode id=438 lang=cpp
 *
 * [438] Find All Anagrams in a String
 */
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        if(s.size() < p.size())
            return res;
        //  p的字符出现频率
        vector<int> freq_p(26,0);
        for(char c:p)
            freq_p[c - 'a'] += 1;
        // s字符的出现频率
        vector<int> freq_s(26,0);
        // 初始化滑动窗口 
        int l = 0, r = -1; 
        while(r+1 < s.size()){
            // 向右扩展
            ++r;
            ++freq_s[s[r] - 'a'];
            // 当窗口长度过长时, 左边收缩，同时改变表元素值
            if(r-l+1 > p.size())
                freq_s[s[l++]-'a']--;
            // 窗口大小及hash相同时
            if(r-l+1 == p.size() && same(freq_s,freq_p))
                res.push_back(l);
        }
        return res;
    }
private:
    bool same(const vector<int>& freq_s,const vector<int>& freq_p){
        for(int i=0;i<26;++i){
            if(freq_s[i] != freq_p[i])
                return false;
        }
        return true;
    }
};

