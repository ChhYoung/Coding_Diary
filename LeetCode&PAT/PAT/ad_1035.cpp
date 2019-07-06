#include<string>
#include<iostream>
using namespace std;
void is_correct(char& a,bool& m){
    if(a=='1'){
        a='@';
        m = false;
    }
    else if(a=='l'){
        a='L';
        m = false;
    }
    else if(a=='0'){
        a='%';
        m = false;
    }
    else if(a=='O'){
        a='o';
        m = false;
    }
}

int main(){
    int N;
    cin>>N;
    int cnt=0;
    string ID[N],PWD[N];
    for(int i=0;i<N;++i){
        bool m=true;
        string id,pwd;
        cin>>id>>pwd;
        for(auto &c:pwd){
            is_correct(c,m);
        }
        if(!m){
            ID[cnt] = id;
            PWD[cnt++] = pwd;
        }
    }
    if(cnt == 0){
        if(N==1)
            printf("There is %d account and no account is modified",N);
        else 
            printf("There are %d accounts and no account is modified",N);
    }
    else {
        cout<<cnt<<"\n";
        for(int i=0;i<cnt;++i){
            cout<<ID[i]<<' '<<PWD[i];
            if(i!=cnt-1) cout<<'\n';
        }
    }
    return 0;
}