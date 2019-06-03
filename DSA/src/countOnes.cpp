#include<iostream>
#define POW(c) (1 << (c))  // 2^c
//生成分组相加用的掩码
#define MASK(c) (((unsigned long)-1) / (POW(POW(c)) + 1))
//移位相加
#define ROUND(n,c) (((n) & MASK(c)) + ((n) >> POW(c) & MASK(c)))

using namespace std;
int countOnes_1(unsigned int n){
    int ones = 0;
    while(n > 0){
        ones += (n & 1);
        n>>=1;
    }
    return ones;
}

int countOnes_2(unsigned int n){
    int ones = 0;
    while(n > 0){
        ones ++ ;
        n &= n-1;
    }
    return ones;
}


int countOnes_3(unsigned int n){
    n = ROUND(n,0);
    n = ROUND(n,1);
    n = ROUND(n,2);
    n = ROUND(n,3);
    n = ROUND(n,4);
    return n;
}

int main(){
    cout<<"countOnes_1(3) = "<<countOnes_1(3)<<endl;
    cout<<"countOnes_2(4) = "<<countOnes_1(4)<<endl;
    cout<<"countOnes_3(5) = "<<countOnes_1(5)<<endl;
    return 0;
}
