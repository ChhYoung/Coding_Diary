// this 的显式调用
#include<iostream>

class Point{
public: 
    Point(int x,int y){X = x;Y = y;}
    Point(){X = 0;Y = 0;}
    void copy(Point& obj);
    void displayxy();
private:
    int X;
    int Y;
};

void Point::copy(Point& obj){
    if(this != &obj)
        *this = obj;
}

void Point::displayxy(){
    std::cout<<X<<" ";
    std::cout<<Y<<std::endl;
}

int main(){
    Point obj1(10,20),obj2;
    obj2.copy(obj1);
    obj1.displayxy();
    obj2.displayxy();
    Point* c = new Point(1,2);
    return 0;
}