#include<iostream>

using namespace std;
/*
class Solution{
public:
    int climbStairs(int n){
        if(n <= 0)
            return 0;
        else if(n == 1)
            return 1;
        else if(n == 2)
            return 2;
        return climbStairs(n-2)+climbStairs(n-1);
    }    
};*/
class Solution{
public:
    int climbStairs(int n){
		int prev = 0;
        int cur = 1;
        for(int i = 1; i<= n;++i){
            int tmp = cur;
            cur += prev;
            prev = tmp;
        }
        return cur;
    }    
};

int main(){
    int input1=44,input2=3;
    cout<<Solution().climbStairs(input1)<<'\n';
    cout<<Solution().climbStairs(input2)<<'\n';
    return 1;
}
