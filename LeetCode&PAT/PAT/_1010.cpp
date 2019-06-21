/* 
#include<iostream>
#include<vector>

using namespace std;

int main(){
    vector<int> k;
    int i;
    while(cin>>i)
        k.push_back(i);
    for(int i=0;i<k.size();i++){
        if(i%2==0)
            k[i] *= k[i+1];
    }
    for(int i=0;i<k.size();i++){
        if(i%2==1)
            k[i] -= 1;
    }
    for(int i=0;i<=k.size()-2;i+=2){
        if(k[0]==0 && k[1]==-1){
            cout<<0;
            break;
        }
        if(i != 0 && k[i+1]!=-1)
            cout<<" ";
        if(i%2 == 0 && k[i+1]!=-1){
            cout<<k[i]<<" "<<k[i+1];
        }
    }
    return 0;
}
*/

#include<iostream>
using namespace std;
int main(){
    int a,b,flag=0;
    while(cin>>a>>b){
        if(b!=0){
            if(flag == 1) cout<<" ";
            cout<<a*b<<" "<<b-1;
            flag = 1;
        }
    }
    if(flag == 0) cout<<"0 0";
    return 0;
}