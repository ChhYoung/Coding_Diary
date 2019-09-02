#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

int main(){
    int N;
    long long p;
    cin>>N>>p;
    vector<int> vec;
    for(int i=0;i<N;++i){
        int m;
        cin>>m;
        vec.push_back(m);
    }
    sort(vec.begin(),vec.end());
    int res = 0, temp = 0;
    for(int i=0;i<N;++i){
        for(int j=i+res; j<N;++j){
            if(vec[j] <= vec[i]*p){
                temp = j-i+1;
                if(res < temp) 
                    res = temp;
            }
            else break;
        }
    }
    cout<<res;
    return 0;
}