#include<string>
#include<iostream>
#include<unordered_map>

using namespace std;

int main(){
    string str1,str2;
    
    cin>>str1;
    cin>>str2;
    unordered_map<char,int> map;
    for(auto& i:str1){
        ++map[i];
    }
    int res = 0;
    for(auto& i:str2){
        if(map[i] > 0){
            --map[i];
        }
        else ++res;
    }
    if(res != 0)
        cout<<"No "<<res;
    else
        cout<<"Yes "<<str1.length()-str2.length();
    return 0;

}
