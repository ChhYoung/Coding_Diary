#include<iostream>
#include<cstdio>
using namespace std;
int main(){
    long long  a,b,c,d,e,f;
    scanf("%lld.%lld.%lld %lld.%lld.%lld",&a,&b,&c,&d,&e,&f);
    long long flag = 0,cnt1=0,cnt2=0,cnt3=0;
    cnt1 = (c+f)%29;
    flag = (c+f)/29;

    cnt2 = (b+e+flag)%17;
    flag = (b+e+flag)/17;
    
    cnt3 = flag + a + d;
    cout<<cnt3<<"."<<cnt2<<"."<<cnt1;
    return 0;
}