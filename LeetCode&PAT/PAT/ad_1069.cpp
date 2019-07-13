#include<iostream>
#include<algorithm>
using namespace std;
bool cmp(char a,char b){return a>b;}
int main(){
    string str;
    cin>>str;
    str.insert(0,4-str.length(),'0');
    do{
        string a=str,b=str;
        sort(a.begin(),a.end(),cmp);
        sort(b.begin(),b.end());
        int  result = stoi(a)-stoi(b);
        str = to_string(result);
        str.insert(0,4-str.length(),'0');
        cout<<a<<" - "<<b<<" = "<<str<<endl;
    }while(str != "6174" && str != "0000");
    return 0;
}