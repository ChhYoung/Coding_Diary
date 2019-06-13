// complex.cpp
#include<iostream>
#include<string>

class Complex{
private: 
    double re,im;
public: 
    Complex(double re=0.0, double im=0.0);
    Complex operator+(Complex c);
    Complex operator-(Complex c);
    void display();
};

Complex::Complex(double r,double i){
    re = r;
    im = i;
}

Complex Complex::operator+(Complex c){
    Complex temp;
    temp.re = re + c.re;
    temp.im = im + c.im;
    return temp;
}

Complex Complex::operator-(Complex c){
    Complex temp;
    temp.re = re - c.re;
    temp.im = im - c.im;
    return temp;
}


void Complex::display(){
    //char str;
    std::string str;
    str = im<0 ? "":"+";
    std::cout<<re<<str<<im<<"i"<<std::endl;
}

int main(){
    Complex c1(3,-4);
    Complex c2(4,5);
    std::cout<<"c1 = ";
    c1.display();
    std::cout<<"c2 = ";
    c2.display();
    Complex c;
    c = c1 + c2;
    std::cout<<"c1 + c2 = ";
    c.display();
    c = c1 - c2;
    std::cout<<"c1 - c2 = ";
    c.display();    
    return 1;
}