// Vector.cpp
#include<iostream>

class Vector{
private: 
    int size;  // 数组大小
    int *array;    

public: 
    Vector(int i = 1);
    Vector(Vector& a);
    int& operator[](int n);
    int operator()();
    Vector& operator+(Vector c);
    Vector& operator-(Vector c);
    Vector& operator=(Vector& c);
    ~Vector();
};

Vector::Vector(int i){
    size = i;
    array = new int[size];
    for(int j=0;j<size;j++){
        array[j]=0;
    }
}

int& Vector::operator[](int n){
    // 下标越界检查
    if(n<0 || n > size){
        std::cout<<"out of range"<<std::endl;
        exit(1);
    }
    return array[n];
}

Vector temp(4);
Vector& Vector::operator+(Vector c){
    for(int i=0;i<4;i++){
        temp[i]=0;
    }
    for(int i=0;i<4;i++){
        temp[i]=array[i]+c.array[i];
    }
    return temp;
}

Vector& Vector::operator-(Vector c){
    for(int i=0;i<4;i++){
        temp[i]=0;
    }
    for(int i=0;i<4;i++){
        temp[i]=array[i]-c.array[i];
    }
    return temp;
}

Vector::Vector(Vector& a){
    array = new int[size];
    if(array){
        for(int i=0;i<4;++i){
            array[i] = a.array[i];
        }
    }
}

Vector& Vector::operator=(Vector& a){
    if(this != &a){
        delete[] array;
        array = new int[size];
        if(array){
            for(int i=0;i<4;i++){
                array[i] = a.array[i];
            }
        }
    }
    return *this;
}

int Vector::operator()(){
    return size;
}

Vector::~Vector(){
    delete[] array;
    size = 0;
}

int main(){
    int j,length;
    Vector X(4),Y(4),Sum(4),Sub(4);
    for(int j=0;j<4;j++){
        X[j] = j+2;
        Y[j] = j*2;
    }
    std::cout<<"vector X = (";
    for(int j=0;j<4;j++){
        int temp=X[j];
        if(j>0)
            std::cout<<",";
        std::cout<<temp;
    }
    std::cout<<")"<<std::endl;

    std::cout<<"vector Y= (";
    for(int j=0;j<4;j++){
        int temp=Y[j];
        if(j>0)
            std::cout<<",";
        std::cout<<temp;
    }
    std::cout<<")"<<std::endl;

    Sum = X + Y;
    Sub = X - Y;

    std::cout<<"vector X+Y= (";
    for(int j=0;j<4;j++){
        int temp=Sum[j];
        if(j>0)
            std::cout<<",";
        std::cout<<temp;
    }
    std::cout<<")"<<std::endl;

    std::cout<<"vector X-Y= (";
    for(int j=0;j<4;j++){
        int temp=Sub[j];
        if(j>0)
            std::cout<<",";
        std::cout<<temp;
    }
    std::cout<<")"<<std::endl;
    length = X();
    std::cout<<"length of the vector is "<<length<<std::endl;
    return 1;
}