#include<iostream>
#include<vector>
#include<string>

using namespace std;
int main(){
    string s;
    cin>>s;
    vector<int> a(10,0);
    for(auto &i:s){
        a[i-'0']++;
    }
    for(int i=0;i<a.size();++i){
        if(a[i]>0){
            cout<<i<<":"<<a[i]<<"\n";
        }
    }
    return 0;
}