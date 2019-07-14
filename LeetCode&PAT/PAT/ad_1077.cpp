#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    int n;
    scanf("%d\n",&n);
    string ans;
    for(int i=0;i<n;++i){
        string str;
        getline(cin,str);
        // 倒置，变成寻找最长公共前缀
        reverse(str.begin(),str.end());
        int len = str.length();
        if(i == 0){
            ans = str;
            continue;
        }
        else{
            int len_ans = ans.length();
            // 看当前前缀  与 当前匹配字符串大大小关系
            if(len < len_ans) swap(ans,str);
            int min_len = min(len,len_ans);
            for(int j=0;j<min_len;++j){
                if(str[j] != ans[j]){
                    ans = ans.substr(0,j);
                    break;
                }
            }
        }
    }
    reverse(ans.begin(),ans.end());
    if(ans.length() == 0){
        cout<<"nai";
    }
    cout<<ans;
    return 0;
}