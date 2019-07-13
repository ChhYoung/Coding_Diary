#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main(){
    string str;
    cin>>str;
    if(str[0]=='-') cout<<'-';
    // 找到小数点位置
    auto ptr_1 = find(str.begin(),str.end(),'.');
    // 找到E的位置
    auto ptr_E = find(str.begin(),str.end(),'E');
    // 判断是否是小数
    bool exp = *(ptr_E+1)=='+'?true:false;
    // 获取每部分数值
    int exp_num = stoi(string(ptr_E+2,str.end()));
    auto exp_num_str = to_string(exp_num);
    int head = str[1]-'0';
    auto head_str = to_string(head);
    
    auto body = string(ptr_1+1,ptr_E);
    int len = body.length();

    if(!exp){
        cout<<"0.";
        for(int i=1;i<=exp_num-1;++i)
            cout<<'0';
        cout<<str[1]<<body;
    }
    else{
        cout<<str[1];
        if(exp_num>len){
            cout<<body;
            for(int i=1;i<=exp_num-len;++i)
                cout<<'0';
        }
        else if(exp_num == len){
            cout<<body;
        }
        else{
            for(int i=0;i<len;++i){
                cout<<body[i];
                if(i+1 ==exp_num)
                    cout<<'.';
            }
        }
    }
    return 0;
}