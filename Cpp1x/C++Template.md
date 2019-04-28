# C++ Template
### meta-programming

---------------------------------------------------

## 1. template基本语法
### template class
**声明**
```cpp
template <typename T> class ClassA;
```
**定义**
```cpp
template <typename T> class classA{
    T memeber;
};
```
**使用**,假设定义一个vector，它有push_back,clear操作
```cpp
template <typename T>
class vector{
public:
        void push_back(T const&);
        void clear();
private:
        T* elements;
};
```
现在程序要一个int和float类型的列表：
```cpp
vector<int> intArray;
vector<float> floatArray;

intArray.push_back(5);
floatArray.push_back(3.0f);
```
1. `vector<int>`将`int`绑定到模板类`vector`上
2. 通过`vector`定义一个变量

**模板类的成员函数定义**
一般内联实现
```cpp
template <typename T>
class vector{
public:
    void clear(){
        // Function body
    }

private:
    T* elements; 
};
```
或者放到类型外(看起来不好)
```cpp
template <typename T>
class vector{
public:
    void clear();
private:
    T* elements;
};

template <typename T>
void vector<T>::clear(){
    // Funtion body
}
```
### template function
**声明与定义**
```C++
template <typename T> void foo(T const& v);
template <typename T> T foo();
template <typename T,typename U> U foo(T const&);
template <typename> void foo(){
    T var;
}
```
使用
```C++
template <typename T> T add(T a, T b){
    return a + b;
}
// 一般指定
int a = 5;
int b = 3;
int result = Add<int>(a,b);
// 编译器推导,模棱两可时不行
int a = 5;
int b = 3;
int result = Add(a,b);
// 指定一部分，推导一部分，将要指定的放前面
// 如，一个类别转换函数
template <typename DstT,typename Srct> DstT c_style_cast(SrcT v){
    return (DstT)(v);
}
int v = 0;
float i = c_style_cast<float>(v);
```
### int也可作template参数
```C++
template <typename T, int Size>struct Array{
    T data[Size];
};
Array<int,16> arr;
```
---------------------------------------------------

## 2 . mate programming
*元编程意味着你撰写一段程序A，程序A会运行后生成另外一个程序B，程序B才是真正实现功能的程序。那么这个时候程序A可以称作程序B的元程序，撰写程序A的过程，就称之为“元编程”。*
```C++
template <typename T> 
class Stack{
public:
    void push(T v);
    T pop();
    T Find(T x){
        for(int i=0;i < size;++i){
            if(data[i] == x){ return i;}
        }
    }
    // 其他代码
};
typedef Stack<int> StackInt;
typedef Stack<float> StackFloat;
```
**特化与偏特化 specialization and partial specialization**
看个例子，假设要编个函数`Variant result=addFloatOrMulInt(aVar,bVar);`,浮点数就相加，整数就相乘，可以重载，可以用if但是不好，模板在编译期就能解决问题,引入template则
```C++
// 这个是给float用的。
template <typename T> class AddFloatOrMulInt
{
    T Do(T a, T b)
    {
        return a + b;
    }
};

// 这个是给int用的。
template <typename T> class AddFloatOrMulInt
{
    T Do(T a, T b)
    {
        return a * b;
    }
};

void foo()
{
    float a, b, c;

    // 嗯，我们需要 c = a + b;
    c = AddFloatOrMulInt<float>::Do(a, b);
    // ... 觉得哪里不对劲 ...
    // ...
    // ...
    // ...
    // 啊！有两个AddFloatOrMulInt，class看起来一模一样，要怎么区分呢！
}
```
这时引入特化，根据一个或者多个特殊的整数或者类型，来给出实例化模板时的一个指定内容
```C++
// 1. 写出模板的一般形式
template<typename T> class AddFloatMulInt{
    static T Do(T a,T b){
        reutrn T(0);
    }
}

// 指定T为int时的代码，这就是特化
template <> class AddFloatMulInt<int>{
public:
    static int Do(int a, int b){
        return a*b;
    }
};

// 指定T为float时的代码
template <> class AddFloatMulInt<float>{
public:
    static float Do(float a, float b){
        return a+b;
    }
};
```
**特化实例**
- 指定指针类型
```C++
template <typename T>
void copy(T* dst, T const* src, size_t elemCount){
    for(size_t i=0; i< elemCount; ++i){
        dst[i] = src[i];
    }
}
```
**不定长模板参数**
**- 默认模板参数**
```C++
template <typename T0, typename T1 = void> struct DoWork;
template <typename T> struct DoWork<T> {};
template <> struct DoWork<int> {};
```
**- 变长模板**
```C++
template <typename... Ts> class Y{};
template <typename... Ts,typename U> class Y<U,TS...>{};
```


