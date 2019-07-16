#include <iostream>
#include <cmath>
using namespace std;
long long a, b, c, d;
long long gcd(long long t1, long long t2) {
    return t2 == 0 ? t1 : gcd(t2, t1 % t2);
}

void func(long long a,long long b){
    if(a*b == 0){
        printf("%s",b == 0?"Inf":"0");
        return;
    }
    // flag == true 则有符号
    bool flag = ((a<0 && b>0) || (a>0 && b<0));
    a = abs(a);
    b = abs(b);
    auto gcd_1 = gcd(a,b);
    a /= gcd_1;
    b /= gcd_1;
    // 假分数头
    auto head = a/b;
    // 假分数分子
    auto res = a%b;
    printf("%s",flag ? "(-":"");
    if(head != 0) cout<<head;
    if(res==0){
        if(flag) printf(")");;
        return ;
    }

    if(head != 0) cout<<" ";
    printf("%lld/%lld",res,b);
    if(flag) printf(")");
}

int main(){
    scanf("%lld/%lld %lld/%lld",&a, &b, &c, &d);
    func(a,b);cout<<" + ";func(c,d);cout<<" = ";func(a*d+c*b,b*d);cout<<endl;
    func(a,b);cout<<" - ";func(c,d);cout<<" = ";func(a*d-c*b,b*d);cout<<endl;
    func(a,b);cout<<" * ";func(c,d);cout<<" = ";func(a*c,b*d);cout<<endl;
    func(a,b);cout<<" / ";func(c,d);cout<<" = ";func(a*d,b*c);
    return 0;
}