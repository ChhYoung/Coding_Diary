#include<iostream>
#include<vector>
#include<iterator>
#include<list>
#include<deque>
#include<algorithm>
#include<string>
#include<functional>
#include<thread>
#include<map>
#include<memory>
#include<unordered_map>
#include<tuple>
#include"my_algorithm.h"
#include<array>
/**********************************************************************/
// 泛型编程风格
// test 1
void test1(){
    int ia1[7] = {1,1,2,3,5,55,89};
    int ia2[4] = {8,13,21,34};
    std::list<int> elems(ia1,ia1+7);
    //std::list<int>::iterator
    auto it = std::find(elems.begin(),elems.end(),55);
    // 在55前面插入 8 13 21 34
    elems.insert(it, ia2, ia2+4);
    for(auto &ele : elems)
        std::cout<<ele<<std::endl;
}
// test 2
// void insert string
void test2(){
    std::string sval{"Part Two"};
    std::list<std::string> slist{"abcd","Part Two"};
    // std::list<std::string>::iterator
    auto it = std::find(slist.begin(),slist.end(),sval);
    slist.insert(it,8,std::string(" dummy "));
    //std::cout<<slist<<std::endl;

    //std::string
    for(auto &i : slist)
        std::cout<<i<<std::endl;
}
// test 3 设计个泛型算法
// 给个vector返回新vector，里面是原vector中大于10的值
template <typename T>
bool less_than(T v1, T v2){
    std::cout<<"未特化 less_than"<<std::endl;
    return v1 < v2 ? true:false;
}
//特化
template <> bool less_than<int>(int v1,int v2){
    //return v1 < v2 ? true:false;
    std::cout<<"特化 less_than<int>"<<std::endl;
    return v1 < v2 ? true:false;
}

template <> bool less_than<float>(float v1,float v2){
    std::cout<<"特化 less_than<float>"<<std::endl;
    return v1 < v2 ? true:false;
}

template <typename T>
bool greater_than(T v1, T v2){
    return v1 > v2 ? true:false;
}
// 算法 
template<typename T>
std::vector<int> filter_ver1(const std::vector<int> &vec,
                        int filter_value,
                        bool (*pred)(T,T) ){
    std::vector<int> nvec;
    for(int ix =0;ix<vec.size();++ix)
        if(pred(vec[ix],filter_value))
            nvec.push_back(vec[ix]);
    return nvec;
}

void test3_2(){
    std::vector<int> vec{1,2,3,6,4,5};
    int filter_value{5};
    auto nvec = filter_ver1<int>(vec,filter_value,less_than<int>);
    for(auto &i: nvec)
        std::cout<<i<<std::endl;
}



void test3_1(){
    if(less_than<float>(1.f,2.f)){
    //if(less_than(1.f,2.f)){
        std::cout<<"v1 is less than v2"<<std::endl;
    }
    else{
        std::cout<<"v1 is not less than v2"<<std::endl;
    }
}

//
void test4(){
    std::vector<int> vec{1,2,3,4,5};
    auto iter1 = find(vec.begin(),vec.end(),5);
    auto iter2 = find(vec.begin(),vec.end(),6);
    if(iter2 == vec.end() && iter1 != iter2)
        std::cout<<"find未找到时返回一个end，但这个end与最后一个元素的end不同"<<std::endl;
    else
        std::cout<<"None"<<std::endl;
}
/*
// test 4
// function object adapter
template< typename InputIterator, typename OutputIterator,
            typename ElmType, typename Comp>
OutputIterator filter_ver2(InputIterator first,InputIterator last,
                            OutputIterator at,const ElmType &val,Comp pred){
        while((first = find_if(first,last,bind2nd())))

}*/
// test 5

void test5(){
    []{
        std::cout<<"lambda 1"<<std::endl;
    }();

    
    auto l = [](const std::string& s){
        std::cout<<s<<std::endl;
    };
    l("lambda 2");
}

// test 6  可变参数模板
int Fac(){
    return 1;
}

template<typename T,typename... Types>
int Fac(T firstArg,Types... args){
    return firstArg*Fac(args...);
}

void test6(){
	std::cout << "1,2,3,4,5的连乘 " << std::endl;
	std::cout << Fac(1, 2, 3, 4, 5) << std::endl;
}
//  test 7 返回最大值
template<int N,int...args>
class Max;

template<int N>
class Max<N> : public std::integral_constant<int,N>
{};

template<int N1, int N2,int ...args>
class Max<N1,N2,args...> : public
    std::integral_constant<int,N1<N2 ?
        Max<N2,args...>::value :
        Max<N1,args...>::value >
{};

void test7(){
    std::cout<<"max element of 5,2,3,4,8,9"<<std::endl;
    std::cout<<Max<5,2,3,4,8,9>::value<<std::endl;
}

// test8 展开循环 dot product
template<int N,typename T>
struct DotProduct{
    static T value(T* x,T* y){
        return *x * *y + DotProduct<N-1,T>::value(x+1,y+1);
    }
};

template<typename T>
struct DotProduct<1,T>{
    static T value(T* x,T*y){
        return *x * *y;
    }
};

template<int N, typename T>
auto dotProcudt(T* x,T* y){
    return DotProduct<N,T>::value(x,y);
}

void test8(){
    int x[2]={1,2};
    int y[2]={3,4};
    std::cout<<dotProcudt<2>(x,y)<<std::endl;
}

void test9(){
    std::vector<int> letters{1,2,3,4,5,6,7,8,9,10};
    auto ptr = letters.end();
    std::cout<<"letter.back: "<<letters.back()<<std::endl;
    std::cout<<"before --ptr: "<<*ptr<<std::endl;
    --ptr;
    std::cout<<"after --ptr: "<<*ptr<<std::endl;
}

// test 10
// 结构化绑定
// 利用tuple返回多个值
// -std=c++17
std::tuple<int, double,std::string> f(){
    return std::make_tuple(1, 2.3, "string:456");
}

void test10(){
    auto [x,y,z] = f();
    std::cout<<x<<",  "<<y<<"  ,  "<<z<<std::endl;
}

// test 11折叠表达式
// C++17
template<typename ...T>
auto sum(T... t){
    return (t + ...);
}
void test11(){
    std::cout<<sum(1,2,3,4,5,6,7,8,9,10)<<std::endl;
}

// lambda 
// lambda捕获
void learn_lambad_1(){
    int value_1 = 1;
    std::cout<<"value of value_1 is "<<value_1<<std::endl;
    //传递引用
    auto copy_value_1 = [&value_1]{
    //值捕获
    //auto copy_value_1 = [value_1]{
        return value_1;
    };
    
    value_1 = 100;
    std::cout<<"value of value_1 is "<<value_1<<std::endl;

    auto stored_value_1 = copy_value_1();

    std::cout<< "value of lambda is "<< stored_value_1<<std::endl;
}

void test12(){
    learn_lambad_1();
}


// TODO : 1. 多参数
//        2. 容器 vector is done
template<typename T,size_t N=0 > void print_every_thing(T a){
    std::cout<<a<<std::endl;
}

template<typename T,size_t N=0> void print_every_thing(std::vector<T> a){
    std::cout<<"elements of this vector is (seperated by , ) :"<<std::endl;
    for(const auto &m : a)
        std::cout<<m<<" , ";
    std::cout<<std::endl;
}

template<typename T,size_t N> void print_every_thing(std::array<T,N> a){
    std::cout<<"elements of this array is (seperated by , ) :"<<std::endl;
    for(const auto &m : a)
        std::cout<<m<<" , ";
    std::cout<<std::endl;
}

template<typename ...T,size_t  N=0> void print_every_thing(std::map<T...> a){
        std::cout<<" map "<<std::endl;
        for(const auto &b:a)
            std::cout<<"Key:["<<b.first<<"] Values:["<<b.second<<"]\n";
};

template<typename ...T,size_t  N=0> void print_every_thing(std::unordered_map<T...> a){
        std::cout<<" unordered_map "<<std::endl;
        for(const auto &b:a)
            std::cout<<"Key:["<<b.first<<"] Values:["<<b.second<<"]\n";
};
/*

void test13(){
    std::vector<int> a{1,2,3,4,5,6};
    std::vector<std::string> b{"abc","bcd"};
	std::array<int, 5> c{ 1,2,3,4,5 };
    std::map<int,std::string> d{
        {1,"1"},
        {4,"4"},
        {2,"2"},
        {3,"3"}
    };
    std::unordered_map<int,std::string> e{
        {1,"1"},
        {4,"4"},
        {2,"2"},
        {3,"3"}
    };
    print_every_thing('a');
    print_every_thing("test13");
    print_every_thing(12);
    print_every_thing(&a);
    print_every_thing(a);
    print_every_thing(b);
    print_every_thing(c);
    print_every_thing(d);
    print_every_thing(e);
}
*/
// test 14

template <int X>
constexpr int fact(){
    return X*fact<X-1>();
}

template <>
constexpr int fact<0>(){
    return 1;
}

void test14(){
    auto x = fact<5>();
    print_every_thing(x);
}

void test15(){
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    print_every_thing(v);
    print_every_thing(v.size());
    print_every_thing(v.capacity());

    v.push_back(4);
    v.push_back(5);
    print_every_thing(v);
    print_every_thing(v.size());
    print_every_thing(v.capacity());

    v.clear();
    print_every_thing(v);
    print_every_thing(v.size());
    print_every_thing(v.capacity());

    v.shrink_to_fit();
    print_every_thing(v);
    print_every_thing(v.size());
    print_every_thing(v.capacity());
}

// array

void test16(){
    std::array<int,5> a={5,3,9,5,1};
    print_every_thing(a);
    std::sort(a.begin(),a.end());
    print_every_thing(a);
}
// test 17 无序容器
// 比较 map 和 unordered_map
void test17(){
    std::unordered_map<int,std::string> u{
        {1,"1"},
        {4,"4"},
        {2,"2"},
        {3,"3"}
    };

    std::map<int,std::string> v{
        {1,"1"},
        {4,"4"},
        {2,"2"},
        {3,"3"}
    };
}

// test 18 tuple 
auto get_tuple(){
    return std::make_tuple(3.5, 'A', "张珊");
}

template <class T>
void test(T t){
    int a[std::tuple_size<T>::value];//编译器运行
    std::cout<<std::tuple_size<T>::value<<'\n'; // 运行期使用
    //print_every_thing(a);
}

void test18(){
     auto student = get_tuple();
     test(get_tuple());
}

// test 19
// shared_ptr
void test19(){
    auto pointer = std::make_shared<int> (10);
    auto pointer2 = pointer; //引用计数+1
    auto pointer3 = pointer; //引用计数+1
    
    //通过get()获得原始指针，不会增加引用次数
    int *p = pointer.get();
    print_every_thing(pointer.use_count()); //3
    print_every_thing(pointer2.use_count());//3
    print_every_thing(pointer3.use_count());//3

    pointer.reset();
    //3个指针共享权相同
    print_every_thing(pointer.use_count()); //0
    print_every_thing(pointer2.use_count());//2
    print_every_thing(pointer3.use_count());//2
}

// test 20
// unique_ptr

void test20_1(){
    std::unique_ptr<int> pointer = std::make_unique<int>(10);

    // error : it's  a unique_ptr
    //std::unique_ptr<int> pointer2 = pointer;
}

struct Foo{
    Foo(){print_every_thing("Foo::Foo");}
    ~Foo(){print_every_thing("Foo::~Foo");}
    void foo(){print_every_thing("Foo::foo");}
};

void f(const Foo&){
    print_every_thing("f(const Foo&)");
}

void test20_2(){
    std::unique_ptr<Foo> p1{std::make_unique<Foo>()};
    print_every_thing("1");
    if(p1) p1->foo();
    {   print_every_thing("1");
        std::unique_ptr<Foo> p2{std::move(p1)};
        print_every_thing("1");
        f(*p2);
        print_every_thing("1");
        if(p2) p2->foo();
        print_every_thing("1");
        if(p1) p1->foo();
        print_every_thing("1");
        p1 = std::move(p2);
        print_every_thing("1");
        if(p2) p2->foo();
        print_every_thing("p2被销毁.");
    }
    print_every_thing("1");
    if(p1) p1->foo();
}

// test21  find my_algorithm.h
void test21(){
    std::vector<int> v{9,8,1,4,6,5,2,10};
    auto m = my_algorithm::find(v.begin(),v.end(),10);
    print_every_thing(*m);
}

// test22 search
void test22(){/*
    std::string str1 = "why waste time learning, when ignorance is instantaneous?";
    std::string str2 = "learning";
    std::string str3 = "leearing";*/
    std::vector<int> str1{1,2,3,4,5,6,7,8};
    std::vector<int> str2{2,3,4};
    std::vector<int> str3{6,5};
    auto res1 = std::search(str1.begin(),str1.end(),str2.begin(),str2.end());
    auto res2 = std::search(str1.begin(),str1.end(),str3.begin(),str3.end());
    if(res1 != str1.end()){
        print_every_thing("first element is ");
        print_every_thing(*res1);
        }
    if(res2 != str1.end()){
        print_every_thing("first element is ");
        print_every_thing(*res2);
        }
    else if(res2 == str1.end()){
        print_every_thing("wrong match");
        //print_every_thing(*res2);
        }
}

// test 23
void test23() {
	int res[] = { 1,2,3,4 };
	std::unordered_map<int, int> m = {
		{1,2},
		{3,4},
		{5,6},
		{7,8}
	};

	int res1[] = { 1,m[1],3 };
	print_every_thing(m[1]);
	std::vector<int> a = { res1, res1+2 ,res1+3};
	print_every_thing(a);
}
int main(){
    //test1();
    //test2();
    //test3_2();
    //test4();
    //test5();
    //test6();
    //test7();
    //test8();
    //test9();
    //test10();
    //test11();
    //test12();
    //test13();
    //test14();
    //test15();
    //test16();
    //test17();
    //test18();
    //test19();
    //test20_2();
    //test21();
    //test22();
	test23();
    return 1;
    
}