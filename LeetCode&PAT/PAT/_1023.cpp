#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int main(){
    vector<int> input,num;
    int i=0;
    for(int m=0;m<10;m++){
        cin>>i;
        input.push_back(i);
    }
    for(int j=0;j<input.size();++j){
        for(int m=0;m<input[j];++m){
            num.push_back(j);
        }
    }
    sort(num.begin(),num.end());
    for(int b=0;b<num.size();++b){
        if(num[b]==0)
            continue;
        else {
            swap(num[0],num[b]);
            break;
        }
    }
    for(auto &v:num)
        cout<<v;
    return 0;

}