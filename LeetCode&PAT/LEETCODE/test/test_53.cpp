#include<iostream>
#include<vector>
#include<iterator>
#include<list>
#include<deque>
#include<algorithm>
#include<string>
#include<functional>
#include<thread>
#include<map>
#include<memory>
#include<unordered_map>
#include<tuple>
#include<array>
#include<cmath>
#include<numeric>

#define INT_MIN -32516
using namespace std;

class Solution{
public:
    int maxSubArray(vector<int>& nums){
        int result = INT_MIN,f=0;
        for(int i=0;i<nums.size();++i){
            f = max(f+nums[i],nums[i]);
            result=max(result,f);
        }
        return result;
    }
};

int main(){
    vector<int> nums={-2,1,-3,4,-1,2,1,-5,4};
    cout<<Solution().maxSubArray(nums)<<'\n';
    return 0;
}