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

**this**指向对象本身，由编译器产生的局部量指针，局部于某个对象，只有非静态成员函数(声明时不含 static, friend)才能拥有this指针。

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



创建删除堆对象使用`new` `delete`,要程序员主动管理申请释放

```c++
Point *x =new Point();
```

使用 `new[],delete[]`创建对象数组

## 4. 友元

### 4.1 友元函数： 

有元函数没有this指针

外部函数可以直接访问类的所有成员对象

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

// 外部函数
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

### 5.1 基本知识

`继承`    不继承构造函数及析构函数

根据一个类创建一个新类的过程称为继承(inheritance),派生心类的类称为基类，派生出的为子类。继承可以分为两种：单继承和多继承 

### 5.2 单继承:
#### 5.2.0  public, private , protected的基本区别
- public： 成员在外部也可以直接访问，可以不用成员函数来访问设置公有变量

```c++
class Stduent(){
    public: 
        int score;
};
// 在外部直接访问
Student m;
m.score;
```
- private：只有该类的成员函数和有元才能访问
```c++
class Stduent(){
    public: 
        int score;
};
Student m;
m.score;// wrong 无法在外部直接访问
```
- protected： 与private不同 protected可以在派生类中访问,对于单个成员来说和private一样，但在继承上实现了共享访问与成员隐藏的平衡

```c++
// public.cpp
#include<iostream>

class Point{
public: 
    void setxy(int myx,int myy){X = myx;Y = myy;}
    void movexy(int x,int y){X+=x;Y+=y;}    
private:

protected:
    int X;
    int Y;
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
```



**继承的一般格式**
```c++
class <派生类名> ：<继承方式><基类名>{
private:

protected:

public:
    
};
```


继承方式：

#### 5.2.1 public:
继承基类的公有成员和保护成员，继承的还是公有成员和保护成员,派生类可以访问基类的公有成员

**赋值兼容规则**：

- 派生类的对象可以赋值给基类的对象，基类可以兼容派生类
```c++
DerviedClass d;
BaseClass b;
b = d;
```
- 派生类可以初始化基类的引用，基类可以引用派生类

```c++
DerviedClass d;
BaseClass &b = d;
```

- 派生类的对象的地址可以赋值给指向基类的指针，基类指针可以指向派生类对象

```c++
DerviedClass d;
BaseClass *pd = &d;
```



#### 5.2.2 protected

继承基类的公有成员和保护成员，作为派生的保护成员，派生类的成员函数可以直接访问，外部无法访问基类所有成员

*见 public.cpp*



#### 5.2.3 private

继承基类的公有成员和保护成员，作为派生的私有成员，外部无法访问基类私有成员

例子：

```C++
class Circle:private Point{
    public: 	
    	void setr(int mxy,int myy ,int myr){
            setxy(myx , myy);
            R = myr;
        }
    protected:
    	int R;
};
c.movexy(8,9) // 会出错
```

私有继承使Point类中的成员函数被封装隐藏，不能被外模块调用。要使用则需要在Circle中增加新的外部接口。

```c++
class Circle: private Point{
    public:
    	void setr(int mxy,int myy,int myr){
            setxy(myx,myy);
        }
    	void movexy(int x,int y){
            Point::movexy(x,y);//增加新的外部窗口
        }
    	void display();
    private:
    	int R;
};
```

### 5.3 多继承

**格式：**

```c++
class <类名> : <继承方式1> <基类名1> ,<继承方式2> <基类名2>
```

**例子**

```c++
// mul-public.cpp
#include<iostream>

class Baseclass1{
private: 
    int a;
public:     
    void seta(int x){a = x;}
    void showa(){std::cout<<"a is "<<a<<"\n";}    
};

class Baseclass2{
private: 
    int b;
public:     
    void setb(int x){b = x;}
    void showb(){std::cout<<"b is "<<b<<"\n";}    
};

class DerivedClass:public Baseclass1,private Baseclass2{
private: 
    int c;

public:     
    void setbc(int x,int y){setb(x);c = y;}
    void showbc(){showb();std::cout<<"c is "<<c<<"\n";}
};

int main(){
    DerivedClass obj;
    obj.seta(5);
    obj.setbc(6,7);
    obj.showa();
    obj.showbc();
    // 错误，外部无法访问
    //obj.showb();
    return 1;
}
```

#### 5.3.1 二义性：

基类间或基类的基类间有相同名字的成员时，

**消除二义性的方法**

- 采用作用域运算符 `<类名>::<成员名>`来消除二义性。

- 继承方式前加`virtual`关键字，则这几个基类共享这个同名成员

### 5.4 构造函数与析构函数

格式

```c++
<派生类名>::<派生类名>(总参数列):<基类名1>(参数1)，<基类名2>(参数2)
```

**例子**

```c++
// class_constructor.cpp
#include<iostream>

class Base{
private:    
    int a;
public: 
    Base(int x){
        a = x;
        std::cout<<"consructing base\n";}
    ~Base(){
        std::cout<<"desructing base\n";
    }    
};

class Derivedclass:public Base{
private: 
    int b;
public:     
    Derivedclass(int i,int j);   
    ~Derivedclass(){
        std::cout<<"desructing derived class\n";
    } 
};

Derivedclass::Derivedclass(int i,int j):Base(i){
    b = j;
    std::cout<<"consructing derived class\n";
}

int main(){
    Derivedclass x(5,6);
    return 1;
}
```

#### 5.4.1 构造函数的调用顺序：

基类，派生类子类，派生类

- 其中在同一层次的构造顺序取决与定义派生类时基类的顺序

- 同一层次中虚基类构造函数的调用优于普通基类的构造函数的调用
- 在多层次中同一虚基类构造函数只被调用一次

```c++
// virtual_cons.cpp
#include<iostream>

class Base_1{
public:
    Base_1(){
        std::cout<<"constructing base_1\n";
    }
};

class Base_2{
public:
    Base_2(){
        std::cout<<"constructing base_2\n";
    }
};

class Derived_1:public Base_2,virtual public Base_1{
public:
    Derived_1(){
        std::cout<<"constructing Derived_1\n";
    }
};

class Derived_2:public Base_2,virtual public Base_1{
public:
    Derived_2(){
        std::cout<<"constructing Derived_2\n";
    }
};

class Derived_3:public Derived_2,virtual public Derived_1{
public:
    Derived_3(){
        std::cout<<"constructing Derived_3\n";
    }
};

int main(){
    Derived_3 obj;
    return 1;
}
```

**结果**

```c++
constructing base_1
constructing base_2
constructing Derived_1
constructing base_2
constructing Derived_2
constructing Derived_3
```

## 6. 多态与虚函数

**多态性：**

### 6.1 联编：

对一个函数的调用，在编译或运行时将其代码链接到对应的函数体上。

#### 6.1.1 静态联编

在编译期就完成

```c++
// li5_2.cpp
// 静态联编

#include<iostream>

const double PI = 3.1415926;

class Figure{
public:     
    Figure(){};
    double area() const {return 0.0;}    
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
// 由于在编译期就已经完成，将p的area联编到Figure的area上，所以输出结果都是0，
// 需要采用 动态联编；或者单个调用 c.area(),d.area()
```

解决方法

```c++
// li5_2.cpp
// 静态联编

#include<iostream>

const double PI = 3.1415926;

class Figure{
public:     
    Figure(){};
    virtual double area() const {return 0.0;}    
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
```



#### 6.1.2 动态联编

采用 `virtual`

**虚函数与重载的区别**

- 虚函数要求函数签名，返回类型相同
- 虚函数只能是非静态类型
- 构造函数可以重载，析构函数不能重载，而构造函数不能为虚函数，析构函数可以为虚函数
- 重载是根据参数的区别，虚函数是根据对象的不同
- 重载是静态，虚函数是动态

**构造函数与析构函数中调用虚函数：**

调用是采用静态联编，调用的虚函数是自己定义的

**纯虚函数**

不能在基类中给出有意义的实现时，用纯虚函数提供个接口

不能在构造函数与析构函数中调用纯虚函数

`virtual <返回值><函数名>(形参列表) = 0`

`virtual double area() const = 0;`

**抽象类**

包含虚函数的类

```c++
class Figure{
public:     
    Figure(){};
    virtual double area() const = 0;    
};

Figure fig;//出错，不能申明抽象类的对象
```

**虚析构函数**

尽量将析构函数申明为虚函数，否则在使用基类性指针时`delete`时派生类有的无法撤销

```c++
// virtual_des.cpp
// virtual destructor
#include<iostream>

class Base{
public: 
    Base(){};
    ~Base(){
        std::cout<<" Base destructor\n";
    }    
};

class Subclass:public Base{
private: 
    int *ptr;
public: 
    Subclass();
    ~Subclass();
};

Subclass::Subclass(){
    ptr = new int;
}

Subclass::~Subclass(){
    delete ptr;
    std::cout<<" subclass destructor\n";
}

int main(){
    Base* b = new Subclass;  // 错误
    // Subclass* b = new Subclass; // 正确
    delete b;
    return 1;
}
```

## 7. 重载运算符

### 7.1 用成员函数重载运算符

**格式**

声明： `<返回值> operate<操作符名> (参数)`

实现 ： `<返回值> operate<操作符名> (参数){}`

```c++
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
```

此处调用操作符时 编译器解释为`c1.operator+(c2)`

若声明为友元,则无法使用this指针，必须声明所有参数

```c++
class Complex{
private: 
    double re,im;
public: 
    Complex(double re=0.0, double im=0.0);
    friend Complex operator+(Complex c1,Complex c2);
    friend Complex operator-(Complex c1,Complex c2);
    void display();
};
Complex operator+(Complex c1,Complex c2){
    
}
```

调用为`c = operator+(c1,c2)`

**n++    ++n运算符的重载**

- pre-increament:     `T operator++()`
- post-increament: `T operator++(int)`

```c++
// pre_incre.cpp
#include<iostream>

class Counter{
private: 
    unsigned int value;
public: 
    Counter(){value = 0;}
    Counter(int i){value = i;}
    Counter operator++();// pre increament
    Counter operator++(int); // post increament
    Counter operator--();// pre decreament
    Counter operator--(int); // post decreament
    void display();
};

Counter Counter::operator++(){
    value ++;
    return *this;
}

Counter Counter::operator++(int){
    Counter temp;
    temp.value = value;
    value++;
    return temp;
}

Counter Counter::operator--(){
    value --;
    return *this;
}

Counter Counter::operator--(int){
    Counter temp;
    temp.value = value;
    value--;
    return temp;
}

void Counter::display(){
    std::cout<<"the value is "<<value<<std::endl;
}

int main(){
    Counter n(10),c;
    c = ++n;
    std::cout<<"pre increament: \n";
    std::cout<<"n = ";
    n.display();
    std::cout<<"c = ";
    c.display();

    c = n++;
    std::cout<<"post increament: \n";
    std::cout<<"n = ";
    n.display();
    std::cout<<"c = ";
    c.display();

    c = --n;
    std::cout<<"pre decreament: \n";
    std::cout<<"n = ";
    n.display();
    std::cout<<"c = ";
    c.display();

    c = n--;
    std::cout<<"post decreament: \n";
    std::cout<<"n = ";
    n.display();
    std::cout<<"c = ";
    c.display();
    return 1;
}
```

友元则

```c++
class Counter{
private: 
    unsigned int value;
public: 
    Counter(){value = 0;}
    Counter(int i){value = i;}
    Counter operator++(Counter&);// pre increament
    Counter operator++(Counter&,int); // post increament
    Counter operator--(Counter&);// pre decreament
    Counter operator--(Counter&,int); // post decreament
    void display();
};

Counter operator--(Counter& p){
    p.value--;
    return p;
}
```

### 7.2 赋值运算符的重载

#### 7.2.1 深拷贝与浅拷贝

若类的成员函数有指向动态分配的内存空间，则浅拷贝时，两个对象指向堆的同一个区域，深拷贝时，在堆区再分配一个区域。


```c++
// li6_6.cpp
// 重载赋值运算
#include<iostream>
#include<cstring>

class Namelist{
private: 
    char * name;
    //std::string name;
public:
    Namelist(char const * p){
        name = new char[std::strlen(p)+1];
        if(name != 0)std::strcpy(name,p);
    }    
    ~Namelist(){
        delete [] name;
    }
    Namelist& operator=( char const * p);
    Namelist& operator=(Namelist&);
    void display(){std::cout<<name<<std::endl;}
};

// 重载赋值运算符完成对常量的赋值
Namelist& Namelist::operator=( char const * p){
    name = new char(std::strlen(p)+1);
    if(name != 0){
        std::strcpy(name,p);
    }
    return *this;
}

// 类对象之间的赋值
Namelist& Namelist::operator=(Namelist& a){
    if(this!=&a){
        delete name;
        name = new char[std::strlen(a.name)+1];
        if(name != 0){
            std::strcpy(name,a.name);
        }
    }
    return *this;
}

int main(){
    Namelist n1("right object"),n2("left object");
    std::cout<<"赋值前的数据\n";
    n1.display();
    n2.display();
    n2 = n1;
    std::cout<<"赋值后的数据\n";
    n1.display();
    n2.display();
    return 1;
}
```
```c++
// 用std::string重构 li6_6.cpp

#include<iostream>
#include<string>

class Namelist{
private: 
    std::string*  name;
public: 
    Namelist(std::string p){
        name = new std::string(p);
    }
    ~Namelist(){
        delete name;
    }
    Namelist& operator=(std::string p);
    Namelist& operator=(Namelist&);
    void display(){
        std::cout<<*name;
        std::cout<<" || "<<"string size:"<<name->size()<<std::endl;
    }
};

Namelist& Namelist::operator=(std::string p){
    name = new std::string(p);
    return *this;
}

Namelist& Namelist::operator=(Namelist& a){
    if(this!=&a){
        delete name;
        // the same as above
        // name->clear();
        name = new std::string(*a.name);
    }
    return *this;
}

int main(){
    Namelist n1("right object"),n2("left object"),n3("");
    std::cout<<"赋值前的数据\n";
    n1.display();
    n2.display();
    n3.display();
    n2 = n1;
    n3 = n1;
    std::cout<<"赋值后的数据\n";
    n1.display();
    n2.display();
    n3.display();
    return 1;
}
```

#### 7.2.2 赋值重载运算符与拷贝构造函数的区别

### 7.3 []  ()  运算符

**[]运算符**：以成员函数形式重载，可以用于下标检查

**[]运算符**：创建传递参数的运算符函数
**[]用于访问下标对应的元素**
```c++
template<typename T>
T& Vector<T>::operator[](Rank r) const {
    return elem_[r];
}
```

### 7.4应用实例

设计一个向量类，进行相应运算符的重载，以下标的形式访问个向量的分量，计算和差，并返回向量的长度(维数), $$\vec{X} =(x_1,x_2,x_3,x_4),\vec{Y} =(y_1,y_2,y_3,y_4),\vec{X}-\vec{Y} = (x_1-y_1,x_2-y_2,x_3-y_3,x_4-y_4)$$



