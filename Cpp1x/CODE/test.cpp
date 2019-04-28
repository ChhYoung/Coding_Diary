#include<iostream>
#include<vector>
#include<iterator>
#include<list>
#include<deque>
#include<algorithm>
#include<string>
#include<functional>
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
// test 5 
// function object adapter
template< typename InputIterator, typename OutputIterator,
            typename ElmType, typename Comp>
OutputIterator filter_ver2(InputIterator first,InputIterator last,
                            OutputIterator at,const ElmType &val,Comp pred){
        while((first = find_if(first,last,bind2nd())))

}

int main(){
    //test1();
    //test2();
    //test3_2();
    test4();
    return 1;
}