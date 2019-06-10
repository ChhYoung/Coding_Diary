// constructor.cpp
#include<iostream>

class Point{
public:
    Point();// default constructor
    Point(int x,int y);
    Point(const Point&);// copy constructor
    ~Point(); // destructor
    void display_xy(){
        std::cout<<'('<<X<<','<<Y<<')'<<std::endl;
    }
private:
    int X;
    int Y;
};

Point::Point(int x,int y){
    X = x;
    Y = y;
    std::cout<<"Constructor is called";
    display_xy();
}

Point::Point(const Point& p){
    X = p.X;
    Y = p.Y;
    std::cout<<"Copy constructor is called";
    display_xy();
}

Point::~Point(){
    std::cout<<"Destructor is called\n";
    display_xy();
}

Point func(Point p){
    int x = 20;
    int y = 15;
    Point func_p(x,y);
    return func_p;
}

void test(){
    Point X(15,16);
}
int main(){
    
    Point p1(3,4);
    Point p2 = p1;
    p2 = func(p1);
    test();
    Point *c = new Point(12,16);
    delete c;
    return 1;
}