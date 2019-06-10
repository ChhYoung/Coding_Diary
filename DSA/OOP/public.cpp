#include<iostream>

class Point{
public: 
    void setxy(int myx,int myy){X = myx;Y = myy;}
    void movexy(int x,int y){X+=x;Y+=y;}    
private:
    int X;
    int Y;
};

class Circle:public Point{
protected: 
    int R;    
public:     
    void setr(int myx,int myy,int myr){
        setxy(myx)
    }    
}