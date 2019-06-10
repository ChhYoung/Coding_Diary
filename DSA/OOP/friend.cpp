// friend 
#include<iostream>
#include<cmath>
class Point{
public: 
    Point(double x,double y){X = x;Y =y;}
    friend double length(Point& a,Point& b);
private: 
    double X;
    double Y;     
};

double length(Point& a,Point& b){
    double dx = a.X - b.Y;
    double dy = a.Y - b.Y;
    return std::sqrt(dx*dx+dy*dy);
}

int main(){
    Point p1(3,4),p2(0,0);
    std::cout<<"The distance of p1 and p2 is:";
    std::cout<<length(p1,p2)<<std::endl;
    return 1;
}