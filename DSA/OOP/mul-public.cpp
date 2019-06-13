// mul-public.cpp
#include<iostream>

class Baseclass1{
private: 
    int a;
public:     
    void seta(int x){a = x;}
    void showa(){std::cout<<"a is "<<a<<"\n";}    
};

class Baseclass2{
private: 
    int b;
public:     
    void setb(int x){b = x;}
    void showb(){std::cout<<"b is "<<b<<"\n";}    
};

class DerivedClass:public Baseclass1,private Baseclass2{
private: 
    int c;

public:     
    void setbc(int x,int y){setb(x);c = y;}
    void showbc(){showb();std::cout<<"c is "<<c<<"\n";}
};

int main(){
    DerivedClass obj;
    obj.seta(5);
    obj.setbc(6,7);
    obj.showa();
    obj.showbc();
    // 错误，外部无法访问
    //obj.showb();
    return 1;
}