#include<iostream>

using namespace std;

struct node{
    char data;
    int next;
    bool flag = false;
}NODE[100000];

int main(){
    int ad_1,ad_2,n,temp;
    cin>>ad_1>>ad_2>>n;
    for(int i=0;i<n;++i){
        cin>>temp;
        cin>>NODE[temp].data>>NODE[temp].next;
    }

    for(temp=ad_1; temp != -1;temp = NODE[temp].next){
        NODE[temp].flag = true;
    }

    for(temp=ad_2;temp != -1;temp = NODE[temp].next){
        if(NODE[temp].flag == true){
            printf("%05d",temp);
            return 0;
        }
    }
    cout<<"-1";
    return 0;

}