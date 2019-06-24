#include<iostream>
#include<unordered_map>
#include<map>
#include<string>

int main(){
    std::map<int,std::string> u={
        {1,"1"},{3,"3"},{2,"2"}
    };
    std::cout<<u[1].first;
}
