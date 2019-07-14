#include"stack.h"
#include<vector>
#include<iostream>

int main(){
    DSA::Stack<int> stack;
    std::vector<int> vec={1,2,3,4,5,6};
    for(auto& i:vec){
        stack.push(i);
    }
    while(!stack.empty()){
        std::cout<<stack.pop()<<'\n';
    }

    return 1;
    
}