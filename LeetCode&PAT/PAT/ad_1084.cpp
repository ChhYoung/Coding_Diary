#include <iostream>
#include <cctype>

#include<unordered_map>

using namespace std;
int main() {
   
    string str1,str2;
    cin>>str1>>str2;  /*
    string str1 = "7_This_is_a_test";
    string str2 = "_hs_s_a_es";
*/

    unordered_map<char,int> map;
    for(char& i:str2){
        map[tolower(i)]++;
    }
    
    for(char& i:str1){
        if(map.find(tolower(i)) == map.end()){
            cout<<(char)toupper(i);
            map[tolower(i)]++;
        }
    } 

    /* 
    for(auto& i:map){
        cout<<i.first<<i.second<<endl;
    }*/
    return 0;
}