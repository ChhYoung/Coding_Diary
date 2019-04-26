#include<iostream>
#include<type_traits>
template<typename T, typename U>
auto add2(T x, U y) -> decltype(x+y){
    return x+y;
}

template<typename T, typename U>
auto add3(T x,U y){
    return x+y;
}

int main(){
    auto x=1;
    auto y=2;
    
    std::cout<<"decltype and auto"<<std::endl;
    decltype(x+y) z;
    if(std::is_same<decltype(x),int>::value)
        std::cout<<"type x == int"<<std::endl;
    if(std::is_same<decltype(x),float>::value)
        std::cout<<"type x == float"<<std::endl;
    if(std::is_same<decltype(x),decltype(z)>::value)
        std::cout<<"type x == type z"<<std::endl;

    std::cout<<" auto return"<<std::endl;
    auto w = add2<int,double>(1,2.0);
    if(std::is_same<decltype(w),double>::value){
        std::cout<<"w is double"<<std::endl;
    }
    std::cout<<w<<std::endl;

    auto q = add3<double,int>(1.0,2);
    std::cout<<"q: "<<q<<std::endl;
    return 1;
}
