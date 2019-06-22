#include<iostream>
#include<vector>
using namespace std;
bool isPrime(int a){
    for(int i=2;i*i<=a;i++){
        if(a%i == 0)
            return false;
    }
    return true;
}

int main(){
    int M,N,cnt=0;
    vector<int> res={2};
    cin>>M>>N;
    for(int j=3;res.size()<=N;j++){
        if(isPrime(j))
            res.push_back(j);
    }
    for(int k=M-1;k<N;k++){
        cnt++;
        cout<<res[k];
        //if(cnt==1) cout<<" ";
        if(cnt%10 == 0 && k != N-1) cout<<"\n";
        else if(k != N-1) cout<<" ";
        else if(k == N-1) cout<<"\n";
    }
    return 0;
}