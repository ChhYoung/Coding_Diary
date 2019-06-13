// public.cpp
#include<iostream>

class Point{
public: 
    void setxy(int myx,int myy){X = myx;Y = myy;}
    void movexy(int x,int y){X+=x;Y+=y;}    
private:
    //void movexy(int x,int y){X+=x;Y+=y;}    

protected:
    int X;
    int Y;
    //void movexy(int x,int y){X+=x;Y+=y;}    
};

class Circle:public Point{
protected: 
    int R;    
public:     
    void setr(int myx,int myy,int myr){
        setxy(myx,myy);
        R = myr;
    }    
    void display();
};

void Circle::display(){
    std::cout<<"the position of the circle's center is : ";
    // 如果将上面的XY改为private则Circle无法访问
    std::cout<<"("<<X<<","<<Y<<")\n";
    std::cout<<"the radius of the circle is ";
    std::cout<<R<<"\n";
}

int main(){
    Circle c;
    c.setr(4,5,6);
    std::cout<<"display\n";
    c.display();
    c.movexy(7,8);
    std::cout<<"display the new circle\n";
    c.display();
    return 1;
}