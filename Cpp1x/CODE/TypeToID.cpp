#include<iostream>

template<typename T> class TypeToID{
public:
    static int const ID = -2;
};

template <> class TypeToID<float>{
public:
    static int const ID = 1;
};

template <> class TypeToID<int>{
public:
    static int const ID = 2;
};

void Print(){
    std::cout << "ID of float:"<< TypeToID<float> ::ID<<std::endl;
    std::cout << "ID of int:"<< TypeToID<int> ::ID<<std::endl;
    std::cout << "ID of void:"<< TypeToID<void> ::ID<<std::endl;

}

int main(){
    Print();
    return 1;
}