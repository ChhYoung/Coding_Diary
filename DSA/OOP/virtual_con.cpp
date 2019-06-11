// virtual_cons.cpp
#include<iostream>

class Base_1{
public:
    Base_1(){
        std::cout<<"constructing base_1\n";
    }
};

class Base_2{
public:
    Base_2(){
        std::cout<<"constructing base_2\n";
    }
};

class Derived_1:public Base_2,virtual public Base_1{
public:
    Derived_1(){
        std::cout<<"constructing Derived_1\n";
    }
};

class Derived_2:public Base_2,virtual public Base_1{
public:
    Derived_2(){
        std::cout<<"constructing Derived_2\n";
    }
};

class Derived_3:public Derived_2,virtual public Derived_1{
public:
    Derived_3(){
        std::cout<<"constructing Derived_3\n";
    }
};

int main(){
    Derived_3 obj;
    return 1;
}