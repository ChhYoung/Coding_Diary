#include<iostream>
#include<vector> 
#include<algorithm> 

using namespace std;


struct mooncake{
    float price;
    float amount;
    float unit;
};

bool cmp(mooncake a,mooncake b){
    return a.unit > b.unit;
}

int main(){
    int N,D;
    cin>>N>>D;

    vector<mooncake> cake(N);

    for(int i=0;i<N;++i){
        cin>>cake[i].amount;
    }
    for(int i=0;i<N;++i){
        cin>>cake[i].price;
    }
    for(int i=0;i<N;++i){
        cake[i].unit = cake[i].price / cake[i].amount;
    }

    sort(cake.begin(),cake.end(),cmp);

    float res = 0;

    for(int i=0;i<N;++i){
        if(cake[i].amount <= D){
            res += cake[i].price;
            D -= cake[i].amount;
        }
        else{
            res += cake[i].unit * D;
            break;
        }
    }
    printf("%.2f",res);
    return 0;
}