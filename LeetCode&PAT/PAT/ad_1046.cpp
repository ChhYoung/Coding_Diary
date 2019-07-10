#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(){
    int N;
    cin>>N;
    vector<int> D;
    int num;
    cin>>num;
    D.push_back(num);
    for(int i=1;i<N;++i){
        cin>>num;
        D.push_back(num+D[i-1]);
    }

    int M;
    cin>>M;

    for(int i=0;i<M;++i){
        int a,b;
        cin>>a>>b;
        int max_num = max(a,b);
        int min_num = min(a,b);
        int dis_A = D[max_num-2]-D[min_num-2];
        cout<<min(dis_A, D[N-1]-dis_A);
        if(i!=M-1) cout<<'\n';
    }


    return 0;
}


/* 
int main(){
    int N;
    cin>>N;
    vector<int> D;
    for(int i=0;i<N;++i){
        int n;
        cin>>n;
        D.push_back(n);
    }
       
    int M;
    cin>>M;
    int sum=0;
    for(auto &i:D){
        sum += i;
    }

    for(int i=0;i<M;++i){
        int a,b;
        cin>>a>>b;
        if(a == b) cout<<0;
        else{
        int ma = max(a,b);
        int mi = min(a,b);
        int sum_1 = 0;
        for(int i=mi-1;i<=ma-2;++i)
            sum_1 += D[i];
        cout<<min(sum_1,sum-sum_1);
        }
        if(i!=M-1) cout<<'\n';
    }
    return 0;
}
*/