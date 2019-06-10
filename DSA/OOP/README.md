# C++ OOP
[TOC]

## 1. constructor , destructor , copy constructor 

### constructor:
### destructor : 
`~Point();`
`Point::~Point();`
在对象释放时被调用。静态分配的对象释放时按照栈的规则调用析构函数。
### copy constructor
用一个已经存在的对象去初始化另一个对象，为了保证引用的对象不被修改,通常使用常量`Point(const Point&);`
- 拷贝构造的三种调用情况：
  - 用类的一个对象去初始化另一个对象
  - 一个对象以值传递的方式传入函数
  - 一个对象以值传递的方式传入另一个对象

以上三个的测试代码：
```c++
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
    return 1;
}
```

**结果：**

> Constructor is called(3,4)
> Copy constructor is called(3,4)
> Copy constructor is called(3,4)     // 传值给 func(Point p)中的p
> Constructor is called(20,15)
> Destructor is called
> (20,15)
> Destructor is called
> (3,4)
> Constructor is called(15,16)
> Destructor is called
> (15,16)
> Destructor is called
> (20,15)
> Destructor is called
> (3,4)

## 2. this

**this**指向对象本身，由编译器参数的局部量指针，局部于某个对象，只有非静态成员函数(声明时不含 static, friend)才能拥有this指针。

- this的隐式调用

```c++
void Point::display_xy(){
    std::cout<<'('<<X<<','<<Y<<')'<<std::endl;
    // 相当于
   // std::cout<<'('<<this->X<<','<<this->Y<<')'<<std::endl;
}
```

- this显式调用

## 3.子对象与堆对象

### 3.1 子对象

**声明：**当一个对象A作为另外一个对象B的成员时，这个对象A称为子对象

**初始化：**`<X>::<X>(参数列表):<成员>(参数列表)`

```c++
// object_1.cpp
// 子对象初始化
#include<iostream>

class Part{
public: 
    Part();
    Part(int x);
    ~Part();
private:
    int val;        
};

Part::Part(){
    val = 0;
    std::cout<<"Default Constructor of Part\n";
}

Part::Part(int x){
    val = x;
    std::cout<<"Constructor of Part\n";
}

Part::~Part(){
    std::cout<<"Destructor of Part\n";
}

class Whole{
public: 
    Whole(int i,int j);
    Whole(){};
    ~Whole();
private: 
    Part p1; // 子对象
    Part p2; // 子对象    
    int data;
};

Whole::Whole(int i,int j):p1(),p2(i),data(j){
    std::cout<<"Constructor of Whole\n";
}

Whole::~Whole(){
    std::cout<<"Destructor of Whole\n";
}

int main(){
    Whole w(3);
    return 1;
}
```

有结果可知，子对象p构造完后在构造w对象

### 3.2 堆对象

C++ 程序的内存格局的4个区

- 数据区 data area : 全局变量静态数据，常量
- 代码区 code area : 所有类成员函数，非成员函数代码
- 栈区 stack area ： 运行函数所分配的局部变量，函数参数，返回数据，返回地址
- 堆区 heap area ： 其余都在堆区



创建删除堆对象使用`new` `delete`

```c++
Point *x =new Point();
```

使用 `new[],delete[]`创建对象数组

## 4. 友元

### 4.1 友元函数： 外部函数可以直接访问类的所有成员对象

```c++
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
```

### 4.2 友元类

```c++
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
```

## 5. 继承

根据一个类创建一个新类的过程称为继承(inheritance),派生心类的类称为基类，派生出的为子类。继承可以分为李两种：单继承和多继承 

### 5.2 单继承:

```c++
class <派生类名> ：<继承方式><基类名>{
private:

protected:

public:
    
};
```

继承方式：

#### 5.2.1**public:**
继承基类的公有成员和保护成员，继承的还是公有成员和保护成员,无法访问基类私有成员,

派生类可以访问基类的公有成员

赋值兼容规则：

- 派生类的对象可以赋值给基类的对象
```c++
DerviedClass d;
BaseClass b;
b = d;
```
- 派生类可以初始化基类的引用

```c++
DerviedClass d;
BaseClass &b = d;
```

- 派生类的对象的地址可以赋值给指向基类的指针

```c++
DerviedClass d;
BaseClass *pd = &d;
```

```c++

```



#### 5.2.2**protected**



#### 5.2.3**private**

继承基类的公有成员和保护成员，作为派生的私有成员，无法访问基类私有成员

