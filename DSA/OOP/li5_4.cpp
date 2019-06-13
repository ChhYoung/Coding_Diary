// li5_4.cpp
#include<iostream>

const double PI = 3.1415926;

class Figure{
public:     
    Figure(){};
    //virtual double area() const = 0;    
    virtual double area() const {return 0;}
};

class Circle:public Figure{
private: 
    double R;
public:
    Circle(double myr){ R = myr;}
    double area() const {return R*R*PI;}       
};

class Rectangle:public Figure{
private: 
    double l,w;
public:
    Rectangle(double myl,double myw){ l = myl;w = myw;}
    double area() const {return l*w;}       
};

void Func(Figure &p){
    std::cout<<p.area()<<std::endl;
}

int main(){
    Figure fig;
    std::cout<<"area of figure is ";
    Func(fig);
    Circle c(1.0);
    std::cout<<"area of circle is ";
    Func(c);
    Rectangle d(2,3);
    std::cout<<"area of rectangle is ";
    Func(d);
    return 1;
}