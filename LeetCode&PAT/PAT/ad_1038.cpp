#include<string>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

bool cmp(string a, string b){
    return a+b < b+a;
}

int  main(){
    int N;
    cin>>N;
    vector<string> str;
    for(int i=0;i<N;++i){
        string str1;
        str.push_back(str1);
    }
    sort(str.begin(),str.end(),cmp);
    string ans;
    for(int i=0;i<N;++i){
        ans += str[i];
    }
    // 去除先导0
    while(ans.size() != 0 && ans[0] == '0'){
        ans.erase(ans.begin());
    }
    if(ans.size() == 0) cout<<0;
    else cout<<ans;
    return 0;

}