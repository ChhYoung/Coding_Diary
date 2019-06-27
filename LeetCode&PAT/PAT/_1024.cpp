#include<iostream>
#include<string>

using namespace std;

int main(){
    string s;
    cin>>s;
    int i=0;
    while(s[i] != 'E') ++i;
    
    string t =s.substr(1,i-1);
    // 指数
    int n = stoi(s.substr(i+1));
    if(s[0]=='-') cout<<"-";

    // 指数小于零
    if(n<0){
        cout<<"0.";
        for(int j=0;j<abs(n)-1;++j) cout<<'0';
        for(int j=0;j<t.length();++j)
            if(t[j]!='.') cout<<t[j];
    }

    // 指数大于零
    else {
        cout<<t[0];
        // cnt 记录t的长度, 
        int cnt,j;
        for(j=2,cnt=0;j<t.length() && cnt<n;++j,++cnt) cout<<t[j];
        // 看是否有小数
        if(j==t.length()){
            for(int k=0;k<n-cnt;++k)
                cout<<'0';
        }
        else{
            cout<<'.';
            for(int k=j;k<t.length();++k)
                cout<<t[k];
        }
    }
    return 0;
}