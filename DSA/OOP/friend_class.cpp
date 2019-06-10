#include<iostream>
#include<cmath>

class Student{
private:
    int number,score;
public:     
    friend class Teacher;
    Student(){};        
};

class Teacher{
private: 
    Student A;
public: 
    Teacher(){};
    Teacher(int i,int j){
        A.number = i;
        A.score = j;
    }
    void display(){
        std::cout<<"No = "<<A.number<<std::endl;
        std::cout<<"Score = "<<A.score<<std::endl;
    }
};

int main(){
    Teacher t1(100,200),t2(300,400);
    t1.display();
    t2.display();
    return 1;
}