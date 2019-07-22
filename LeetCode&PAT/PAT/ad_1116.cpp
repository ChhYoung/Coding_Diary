#include<string>
#include<iostream>
#include<unordered_map>

using namespace std;

bool isPrime(int a){
    for(int i=2;i*i<=a;i++){
        if(a%i == 0)
            return false;
    }
    return true;
}

int main(){
    int n1,n2;
    cin>>n1;
    unordered_map<string,int> map1,map2;
    string a[5] ={"Mystery Award","Minion","Chocolate","Are you kidding?","Checked"};
    for(int i=0;i<n1;++i){
        string temp;
        cin>>temp;
        map2[temp] = 1;
        if(i == 0) 
            map1[temp] = 0;

        else if(isPrime(i+1)){
            map1[temp] = 1;
        }
        else map1[temp] = 2;
    }

    cin>>n2;

    for(int i=0;i<n2;++i){
        string temp;
        cin>>temp;
        if(map2[temp] == 1){
            cout<<temp<<": "<<a[map1[temp]];
            map2[temp]++;
        }
        else if(map2[temp]>1){
            cout<<temp<<": "<<a[4];
        }
        else {
            cout<<temp<<": "<<a[3];
        }
        cout<<endl;
    }

    return 0;

}