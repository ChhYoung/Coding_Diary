#include<cstdio>
#include<vector>
using namespace std;

// 用来存储质数的表
// 素数筛选法
vector<int> prime(500000,1);

int main(){
    for(int i=2; i*i < 500000; ++i){
        for(int j=2; j*i < 500000; ++j){
            prime[j*i] = 0;
        }
    }
    long int a;
    scanf("%ld",&a);
    printf("%ld=",a);
    if(a == 1) {
        printf("1");
        return 0;
    }
    // 利用 state 将乘号交由前面 的来输出，
    // 利用 flag 来输出质数

    bool state = false;
    for(int i=2;a>=2; ++i){
        int cnt = 0,flag=0;
        while(prime[i] == 1 && a % i == 0){
            cnt++;
            a /= i;
            flag = 1;
        }
        if(flag){
            if(state) printf("*");
            printf("%d",i);
            state = true;
        }
        if(cnt >= 2)
            printf("^%d",cnt);
    }
    return 0;
}