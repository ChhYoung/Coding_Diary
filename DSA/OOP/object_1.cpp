// 子对象初始化
#include<iostream>

class Part{
public: 
    Part();
    Part(int x);
    ~Part();
private:
    int val;        
};

Part::Part(){
    val = 0;
    std::cout<<"Default Constructor of Part\n";
}

Part::Part(int x){
    val = x;
    std::cout<<"Constructor of Part\n";
}

Part::~Part(){
    std::cout<<"Destructor of Part\n";
}

class Whole{
public: 
    Whole(int i,int j);
    Whole(){};
    ~Whole();
private: 
    Part p1; // 子对象
    Part p2; // 子对象   
    int data;  
};

Whole::Whole(int i,int j):p1(),p2(i),data(j){
    std::cout<<"Constructor of Whole\n";
}

Whole::~Whole(){
    std::cout<<"Destructor of Whole\n";
}

int main(){
    Whole w(3,1);
    return 1;
}