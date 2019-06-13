// class_constructor.cpp
#include<iostream>

class Base{
private:    
    int a;
public: 
    Base(int x){
        a = x;
        std::cout<<"consructing base\n";}
    ~Base(){
        std::cout<<"desructing base\n";
    }    
};

class Derivedclass:public Base{
private: 
    int b;
public:     
    Derivedclass(int i,int j);   
    ~Derivedclass(){
        std::cout<<"desructing derived class\n";
    } 
};

Derivedclass::Derivedclass(int i,int j):Base(i){
    b = j;
    std::cout<<"consructing derived class\n";
}

int main(){
    Derivedclass x(5,6);
    return 1;
}