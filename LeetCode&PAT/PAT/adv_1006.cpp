#include<string>
#include<iostream>
#include <climits>
using namespace std;

int main(){
    string in_name,out_name,id;
    int in_time = INT_MAX,out_time = INT_MIN;
    int N;
    scanf("%d",&N);
    int h1,m1,s1,h2,m2,s2;
    for(int i=0;i<N;++i){
        cin>>id;
        scanf("%d:%d:%d %d:%d:%d",&h1,&m1,&s1,&h2,&m2,&s2);
        int t1 = h1*3600 + m1*60 + s1;
        int t2 = h2*3600 + m2*60 + s2;
        if(t1<in_time){
            in_time = t1;
            in_name = id;
        }
        if(t2>out_time){
            out_time = t2;
            out_name = id;
        }
    }
    cout<<in_name<<' '<<out_name;
    return 0;
}