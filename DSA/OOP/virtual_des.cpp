// virtual_des.cpp
// virtual destructor
#include<iostream>

class Base{
public: 
    Base(){};
    ~Base(){
        std::cout<<" Base destructor\n";
    }    
};

class Subclass:public Base{
private: 
    int *ptr;
public: 
    Subclass();
    ~Subclass();
};

Subclass::Subclass(){
    ptr = new int;
}

Subclass::~Subclass(){
    delete ptr;
    std::cout<<" subclass destructor\n";
}

int main(){
    Base* b = new Subclass;  // 错误
    // Subclass* b = new Subclass; // 正确
    delete b;
    return 1;
}