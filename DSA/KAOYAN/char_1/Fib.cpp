#include"Fib.h"
#include<iostream>

int main(){
    Fib x{6};
    std::cout<<"Fib(6) = 8"<<std::endl;
    std::cout<<"Get "<<x.get()<<std::endl;
    if(x.get() == 8)
        std::cout<<"pass"<<std::endl;
    return 0;
}