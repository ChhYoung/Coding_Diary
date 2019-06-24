/* 
#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main(){
    int a,b,c,d;
    int cnt=0,res1=0,res2=0;
    cin>>a>>b>>c>>d;
    auto a1 = to_string(a);
    auto b1 = to_string(b);
    auto c1 = to_string(c);
    auto d1 = to_string(d);
    for(int i=0;i<a1.length();i++){
        if(a1[i] == b1[0]){
            cnt++;
        }
    }
    for(int j=1;j<=cnt;j++){
        res1 = 10*res1 + b;
    }
    cnt=0;
    for(int i=0;i<c1.length();i++){
        if(c1[i] == d1[0]){
            cnt++;
        }
    }
    for(int j=1;j<=cnt;j++){
        res2 = 10*res2 + d;
    }
    cout<<res1+res2;
    return 0;
}
*/

#include<iostream>
#include<string>
using namespace std;
int main(){
    string a,b;
    int da,db,pa=0,pb=0;
    cin>>a>>da>>b>>db;
    for(int i=0;i<a.length();i++){
        if(a[i]-'0' == da){
            pa = pa*10 + da;
        }
    }
    for(int i=0;i<b.length();i++){
        if(b[i]-'0' == db){
            pb = pb*10 + db;
        }
    }
    cout<<pa + pb;
    return 0;
}