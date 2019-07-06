#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> vec;
    int n=13,d=2;
    do{
        vec.push_back(n%d);
        n /= d;
    }while(n);

    for(auto i:vec){
        cout<<i;
    }
    cout<<'\n';
    for(int i=vec.size()-1;i>=0;--i){
        cout<<vec[i];
    }
    cout<<'\n';
    return 1;
}