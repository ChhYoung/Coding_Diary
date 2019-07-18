#include<iostream>
#include<cmath>

using namespace std;

long int num,temp;

int main(){
    cin>>num;
    int first = 0, len = 0, maxn = sqrt(num)+1;
    for(int i=2; i<=maxn; ++i){
        int j;
        temp = 1;
        for(j = i; j<=maxn; ++j){
            temp *= j;
            if(num % temp != 0){
                break;
            }
        }
        // j为刚好不匹配时的值，所以长度不用-1
        if(j-i>len){
            len = j - i;
            first = i;
        }
    }    

    if(first == 0){
        cout<<1<<endl<<num;
    }
    else {
        cout<<len<<endl;
        for(int i=0;i<len; ++i){
            cout<<first + i;
            if(i != len-1) cout<<"*";
        }
    }
    

    return 0;
}
