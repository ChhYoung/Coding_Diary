#include<iostream>
#include<vector>
#include<algorithm>
using namespace  std;
int main(){
    int M,N;
    cin>>M>>N;
    vector<int> res;
    for(int i=0;i<M;++i){
        for(int j=0;j<N;++j){
            int num;
            cin>>num;
            res.push_back(num);
        }
    }
    sort(res.begin(),res.end());
    cout<<res[res.size()/2];
    return 0;
}