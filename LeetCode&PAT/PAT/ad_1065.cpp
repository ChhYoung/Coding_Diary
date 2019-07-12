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