/* #include<iostream>
#include<stack>
#include<string>

int main(){
    std::stack<std::string> v;
    std::string s;
    while(std::cin>>s) 
        v.push(s);
    std::cout<<v.top();
    v.pop();
    while(!v.empty()){
        std::cout<<" "<<v.top();
        v.pop();
    }
    return 0;
}*/

#include <iostream>
#include <stack>
using namespace std;
int main() {
    stack<string> v;
    string s;
    while(cin >> s) v.push(s);
    cout << v.top();
    v.pop();
    while(!v.empty()) {
        cout << " " << v.top();
        v.pop();
    }
    return 0;
}