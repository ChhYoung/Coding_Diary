#ifndef CodingDiary_Cpp1x_CODE_MYALGORITHM_H_ 
#define CodingDiary_Cpp1x_CODE_MYALGORITHM_H_ 

#include<vector>
#include<iostream>
#include<algorithm>
/////////////////////////   1
// std::find
// std::find_if
// std::find_if_not
namespace my_algorithm{

template<typename Input,typename T>
Input find(Input first, Input last,const T& value){
    for(;first != last; ++first){
        if(*first == value){
            return first;
        }
    }
    return last;
}

template<typename Input,typename UnaryPredicate>
bool find_if(Input first,Input last,UnaryPredicate p){
    for(;first != last;++first){
        if(p(*first)){
            return first;
        }
    }
    return last;
}

template<typename Input,typename UnaryPredicate>
bool find_if_not(Input first,Input last,UnaryPredicate p){
    for(;first != last;++first){
        if(!p(*first)){
            return first;
        }
    }
    return last;
}

/////////////////////////   2
// std::search
// std::search_n
template<typename ForwardIt1, typename ForwardIt2>
constexpr ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
                            ForwardIt2 s_first, ForwardIt2 s_last){
    for (;;++first){
        ForwardIt1 it = first;
        for (ForwardIt2 s_it{s_first}; ;++it,++s_it){
            // 第二个遍历完
            if (s_it == s_last){
                return first;
            }
            // 第一个遍历完
            if (it == last){
                return last;
            }
            // 有不匹配的则跳出当前循环（第二个for）
            if (!(*it == *s_it)){
                break;
            }
        }
    }
}




}
#endif // CodingDiary_Cpp1x_CODE_MYALGORITHM_H_ 
