/*
 * @lc app=leetcode id=20 lang=cpp
 *
 * [20] Valid Parentheses
 */
#include<stack>
#include<string>

class Solution {
public:
    bool isValid(std::string s) {
        std::stack<char> res;
        for(int i=0;i<s.length();++i){
            if(s[i]=='{' || s[i]=='[' || s[i]=='('){
                res.push(s[i]);
            }
            else {
                if(res.empty()) return false;

                if(s[i]=='}' && res.top()!='{') return false;
                if(s[i]==')' && res.top()!='(') return false;
                if(s[i]==']' && res.top()!='[') return false;
                /* 
                else if(s[i]=='}'){
                    if(res.top()!='{')
                        return false;
                }
                else if(s[i]==')'){
                    if(res.top()!='(')
                        return false;
                }
                else if(s[i]==']'){
                    if(res.top()!='[')
                        return false;
                }*/
                res.pop();
            }
        }
        /* 
        if(res.empty())
            return true;
        else return false;*/
        return res.empty();
    }
};




class Solution {
public:
    bool isValid(std::string s) {
        std::stack<char> res;
        for(int i=0;i<s.length();++i){
            if(s[i]=='{' || s[i]=='[' || s[i]=='(')
                res.push(s[i]);
            else {
                if(res.empty()) return false;
                if(s[i]=='}' && res.top()!='{') return false;
                if(s[i]==')' && res.top()!='(') return false;
                if(s[i]==']' && res.top()!='[') return false;
                res.pop();
            }
        }
        return res.empty();
    }
};

