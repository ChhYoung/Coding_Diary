/*
 * @lc app=leetcode id=155 lang=cpp
 *
 * [155] Min Stack
 */
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

class MinStack {

public:
    /** initialize your data structure here. */
    MinStack() {
        vector<int> mystack;
    }
    
    void push(int x) {
        mystack.push_back(x);
    }
    
    void pop() {
        mystack.pop_back();
    }
    
    int top() {
        return mystack.back();
    }
    
    int getMin() {
        int min=mystack[0];
        for(auto i:mystack){
            min = min<i?min:i;
        }
        return min;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

