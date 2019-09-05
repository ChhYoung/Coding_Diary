#include<iostream>
#include<algorithm>
using namespace std;
int dp[1010][1010];
int main(){
    fill_n(&dp[0][0],1010*1010,0);
    string str;
    cin>>str;
    int len = str.length(), maxL = 1;
    for(int i=0; i<len; ++i){
        dp[i][i] = 1;
        if(i < len - 1 && str[i] == str[i+1]){
            dp[i][i+1] = 1;
            maxL = 2;
        }
    }

    for(int l=3 ; l<=len; ++)
}