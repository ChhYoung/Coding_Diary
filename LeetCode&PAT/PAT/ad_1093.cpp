#include<iostream> 
#include<string> 

using namespace std;

int main(){
    string a;
    cin>>a;
    int count_T = 0,count_P = 0,res = 0;
    for(int i=0;i<a.length();++i){
        if(a[i]=='T')
            count_T++;
    }

    for(int i=0;i<a.length();++i){
        if(a[i] == 'P') 
            ++count_P;
        if(a[i] == 'A')
            res = (res+count_P*count_T)%1000000007;
        if(a[i] == 'T')
            --count_T;
    }
    cout<<res;
    return 0;

}