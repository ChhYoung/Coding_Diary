#include<complex>
#include<type_traits>
#include<iostream>

template <typename T> T CustomDiv(T lhs, T rhs){
    T v;
    return v;
}
/*
template <
    typename T,
    bool IsFloat = std::is_floating_point<T>::value,
    bool IsIntegral = std::is_integral<T>::value
> struct SafeDivide{
    static T Do(T lhs, T rhs){
        return CustomDiv(lhs,rhs);
    }
};

template<typename T> struct SafeDivide<T,true,false>{
    static T Do(T lhs, T rhs){
        return lhs/rhs;
    }
};

template<typename T> struct SafeDivide<T,false,true>{
    static T Do(T lhs, T rhs){
        return rhs == 0 ? 0 : lhs/rhs;
    }
};
*/

//只使用一个条件量来分配
template <typename T,typename Enable = std::true_type> struct SafeDivide{
    static T Do(T lhs, T rhs){
        return CustomDiv(lhs/rhs);
    }
};

template <typename T> struct SafeDivide<
    T,typename std::is_floating_point<T>::type>{
    static T Do(T lhs, T rhs){
        return lhs/rhs;
    }
};

template <typename T> struct SafeDivide<
    T,typename std::is_integral<T>::type>{
    static T Do(T lhs, T rhs){
        return rhs == 0 ? 0 : lhs/rhs;
    }
};

void foo(){
    std::cout<<SafeDivide<float>::Do(1.0f,2.0f)<<std::endl;
    std::cout<<SafeDivide<int>::Do(1,2)<<std::endl;
    std::cout<<SafeDivide<std::complex<float>>::Do({1.f,2.f},{1.f,-2.f})<<std::endl;   
}

int main(){
    foo();
    return 1;
}
