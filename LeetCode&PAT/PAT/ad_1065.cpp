#include<cstdio>
using namespace std;
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        long long a,b,c;
        scanf("%lld %lld %lld",&a,&b,&c);
        long long sum = a+b;
        // 溢出
        if(a>0 && b>0 && sum< 0){
            printf("Case #%d: true\n",i+1);
        }
        else if(a<0 && b<0 && sum>= 0){
            printf("Case #%d: fasle\n",i+1);
        }
        else if(sum > c){
            printf("Case #%d: true\n",i+1);
        }
        else {
            printf("Case #%d: false\n",i+1);
        }
    }
    return 0;
}














/* 
#include<iostream>
using namespace std;
int main(){
    long long a,b,c;
    int N;
    cin>>N;
    for(int i=1;i<=N;++i){
        cin>>a>>b>>c;
        cout<<"Case #"<<i<<": ";
        (a+b>c)? cout<<"true":cout<<"false";
        if(i != N) cout<<'\n';
    }
    return 0;
}
*/