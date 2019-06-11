// 用std::string重构 li6_6.cpp

#include<iostream>
#include<string>

class Namelist{
private: 
    std::string *  name;
public: 
    Namelist(std::string p){
        name = new std::string(p);
    }
    ~Namelist(){
        delete name;
    }
    Namelist& operator=(std::string p);
    Namelist& operator=(Namelist&);
    void display(){
        std::cout<<*name;
        std::cout<<" || "<<"string size:"<<name->size()<<std::endl;
    }
};

Namelist& Namelist::operator=(std::string p){
    name = new std::string(p);
    return *this;
}

Namelist& Namelist::operator=(Namelist& a){
    if(this!=&a){
        delete name;
        // the same as above
        //name->clear();
        name = new std::string(*a.name);
    }
    return *this;
}

int main(){
    Namelist n1("right object"),n2("left object"),n3("");
    std::cout<<"赋值前的数据\n";
    n1.display();
    n2.display();
    n3.display();
    n2 = n1;
    n3 = n1;
    std::cout<<"赋值后的数据\n";
    n1.display();
    n2.display();
    n3.display();
    return 1;
}
