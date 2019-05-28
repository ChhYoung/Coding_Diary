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
Input find_if(Input first,Input last,UnaryPredicate p){
    for(;first != last;++first){
        if(p(*first)){
            return first;
        }
    }
    return last;
}

template<typename Input,typename UnaryPredicate>
Input find_if_not(Input first,Input last,UnaryPredicate p){
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

/////////////////////////   3
// std::all_of
// std::any_of
// std::none_of
template<typename InputIt,typename UnaryPredicate>
bool all_of(InputIt first,InputIt last,UnaryPredicate p){
	return find_if_not(first,last,p) == last;
}

template<typename InputIt,typename UnaryPredicate>
bool any_of(InputIt first,InputIt last,UnaryPredicate p){
	return find_if(first,last,p) != last;
}

template<typename InputIt,typename UnaryPredicate>
bool none_of(InputIt first,InputIt last,UnaryPredicate p){
	return find_if(first,last,p) == last;
}


////////////////////////////////
/////////    Manancher's Algorithm

std::string Manancher(std::string s) {
	std::string t = "$#";
	for (int i = 0; i < s.size(); ++i) {
		t += s[i];
		t += "#";
	}
	std::vector<int> p(t.size(), 0);
	int mx = 0, id = 0, resLen = 0, resCenter = 1;
	for (int i = 1; i < t.size(); ++i) {
		p[i] = mx > i ? std::min(p[2 * id - i], mx - i) : 1;
		while (t[i + p[i]] == t[i - p[i]])
			++p[i];
		if (mx < i + p[i]) {
			mx = i + p[i];
			id = i;
		}
		if (resLen < p[i]) {
			resLen = p[i];
			resCenter = i;
		}
	}
	/*
	print_every_thing(resCenter);
	print_every_thing(resLen);*/
	return s.substr((resCenter - resLen) / 2, resLen - 1);
}

/////////////////////// 
////  print_every_thing
// TODO : 1. 多参数
//        2. 容器 vector is done
template<typename T, size_t N = 0 > void print_every_thing(T a) {
	std::cout << a << std::endl;
}

template<typename T, size_t N = 0> void print_every_thing(std::vector<T> a) {
	std::cout << "elements of this vector is (seperated by , ) :" << std::endl;
	for (const auto& m : a)
		std::cout << m << " , ";
	std::cout << std::endl;
}

template<typename T, size_t N> void print_every_thing(std::array<T, N> a) {
	std::cout << "elements of this array is (seperated by , ) :" << std::endl;
	for (const auto& m : a)
		std::cout << m << " , ";
	std::cout << std::endl;
}

template<typename ...T, size_t  N = 0> void print_every_thing(std::map<T...> a) {
	std::cout << " map " << std::endl;
	for (const auto& b : a)
		std::cout << "Key:[" << b.first << "] Values:[" << b.second << "]\n";
}

template<typename ...T, size_t  N = 0> void print_every_thing(std::unordered_map<T...> a) {
	std::cout << " unordered_map " << std::endl;
	for (const auto& b : a)
		std::cout << "Key:[" << b.first << "] Values:[" << b.second << "]\n";
}


}
#endif // CodingDiary_Cpp1x_CODE_MYALGORITHM_H_ 
