#include<iostream>
#include<string>

using namespace std;

int main(){
    string str1;
    int N;
    cin>>N;
    cin>>str1;
    int cnt = 0;
    for(int i=1;i<str1.length();++i){
        if(str1[i-1] == str1[i]){
            cnt++;

        }
        else{
            cnt = 0;
        }

    }
}