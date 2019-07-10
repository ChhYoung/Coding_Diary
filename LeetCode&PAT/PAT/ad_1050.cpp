// solution 2 : using hash set
#include<unordered_set>
#include<string>
#include<iostream>

using namespace std;

int main(){
    string s1,s2;
    getline(cin,s1);
    getline(cin,s2);
    unordered_set<char> set;
    for(auto &i:s2){
        set.insert(i);
    }
    for(auto &i:s1){
        if(set.count(i) == 0){
            cout<<i;
        }
    }
    return 0;
}



/* 
// solution 1: time complextity O(n*m)
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    string s1,s2;
    getline(cin,s1);
    getline(cin,s2);

    for(auto &i:s1){
        if(s2.end() == find(s2.begin(),s2.end(),i)){
            cout<<i;
        }
    }
    return 0;

}
*/

