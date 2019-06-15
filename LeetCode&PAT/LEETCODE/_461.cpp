#include<iostream>

class Solution {
public:
    int hammingDistance(int x, int y) {
        int res_1 = x xor y;
        int res = 0;
        while(res_1){
            if(res_1%2)
                res++;
            res_1 = res_1>>1;
        }
        return res;
    }
};

int main(){
    //int m = 4;
    std::cout<<Solution().hammingDistance(1,4)<<"\n";
    std::cout<<Solution().hammingDistance(4,4)<<"\n";
    std::cout<<Solution().hammingDistance(0,0)<<"\n";
    std::cout<<Solution().hammingDistance(1,0)<<"\n";
    std::cout<<Solution().hammingDistance(4,1)<<"\n";
    std::cout<<Solution().hammingDistance(2,4)<<"\n";
    std::cout<<Solution().hammingDistance(15,0)<<"\n";
    return 1;
}