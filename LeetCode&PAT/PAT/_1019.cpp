#include <iostream>
#include <algorithm>
using namespace std;
bool cmp(char a, char b) {return a > b;}
int main() {
    string s;
    cin >> s;
    s.insert(0, 4 - s.length(), '0');
    do{
        string a=s,b=s;
        sort(a.begin(),a.end(),cmp);
        sort(b.begin(),b.end());
        // 转成数字,计算差
        int result = stoi(a) - stoi(b);
        // 转成字符串
        s = to_string(result);
        s.insert(0, 4 - s.length(), '0');
        cout<<a<<" - "<<b<<" = "<<s<<endl;
    }while(s != "6174" && s != "0000");
    return 0;
}