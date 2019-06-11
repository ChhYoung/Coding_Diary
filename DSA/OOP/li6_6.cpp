// li6_6.cpp
// 重载赋值运算
#include<iostream>
#include<cstring>

class Namelist{
private: 
    char * name;
    //std::string name;
public:
    Namelist(char const * p){
        name = new char[std::strlen(p)+1];
        if(name != 0)std::strcpy(name,p);
    }    
    ~Namelist(){
        delete [] name;
    }
    Namelist& operator=( char const * p);
    Namelist& operator=(Namelist&);
    void display(){std::cout<<name<<std::endl;}
};

// 重载赋值运算符完成对常量的赋值
Namelist& Namelist::operator=( char const * p){
    name = new char(std::strlen(p)+1);
    if(name != 0){
        std::strcpy(name,p);
    }
    return *this;
}

// 类对象之间的赋值
Namelist& Namelist::operator=(Namelist& a){
    if(this!=&a){
        delete name;
        name = new char[std::strlen(a.name)+1];
        if(name != 0){
            std::strcpy(name,a.name);
        }
    }
    return *this;
}

int main(){
    Namelist n1("right object"),n2("left object");
    std::cout<<"赋值前的数据\n";
    n1.display();
    n2.display();
    n2 = n1;
    std::cout<<"赋值后的数据\n";
    n1.display();
    n2.display();
    return 1;
}