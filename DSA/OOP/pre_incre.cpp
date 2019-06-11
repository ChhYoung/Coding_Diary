// pre_incre.cpp
#include<iostream>

class Counter{
private: 
    unsigned int value;
public: 
    Counter(){value = 0;}
    Counter(int i){value = i;}
    Counter operator++();// pre increament
    Counter operator++(int); // post increament
    Counter operator--();// pre decreament
    Counter operator--(int); // post decreament
    void display();
};

Counter Counter::operator++(){
    value ++;
    return *this;
}

Counter Counter::operator++(int){
    Counter temp;
    temp.value = value;
    value++;
    return temp;
}

Counter Counter::operator--(){
    value --;
    return *this;
}

Counter Counter::operator--(int){
    Counter temp;
    temp.value = value;
    value--;
    return temp;
}

void Counter::display(){
    std::cout<<"the value is "<<value<<std::endl;
}

int main(){
    Counter n(10),c;
    c = ++n;
    std::cout<<"pre increament: \n";
    std::cout<<"n = ";
    n.display();
    std::cout<<"c = ";
    c.display();

    c = n++;
    std::cout<<"post increament: \n";
    std::cout<<"n = ";
    n.display();
    std::cout<<"c = ";
    c.display();

    c = --n;
    std::cout<<"pre decreament: \n";
    std::cout<<"n = ";
    n.display();
    std::cout<<"c = ";
    c.display();

    c = n--;
    std::cout<<"post decreament: \n";
    std::cout<<"n = ";
    n.display();
    std::cout<<"c = ";
    c.display();
    return 1;
}