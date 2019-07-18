#include<string>
#include<iostream>
#include<cstdlib>

using namespace std;

bool judge(string a){
    int num = 0;
    int num_point = 0;
    for(int i=0;i<a.length();++i){
        if(i==0 || a[0] == '-') {
            continue;
        }

        if(isdigit(a[i]) || (a[i]=='.' && i!=0)){
            auto m = a.find('.');
            if(m == string::npos) {
                continue;
            }
            else{
                ++ num_point;
                auto len = a.length()-m-1;
                if(len > 2 || num_point>1 || len<=0){
                    return false;
                }
            }
        }
        else{
            return false;
        }
    }
    auto k = (a[0] == '-' ) ? stoi(a.substr(1)):stoi(a);
    if(abs(k)>1000)
        return false;
    return true;
}

int main(){
    string a[8] = {"5", "-3.2" ,"aaa","0..." ,"9999" ,"2.3.4" ,"7.123" ,"2.35"};
    for(int i=0;i<8;++i){
        if(!judge(a[i])) cout<<"false"<<endl;
        else cout<<"true"<<endl;
    }
    return 1;
}
