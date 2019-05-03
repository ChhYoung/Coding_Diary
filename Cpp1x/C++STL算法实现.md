# C++ STL算法实现
*不纯粹地造轮子，只是以学习STL算法为主，用STL造STL*
### 不修改序列的操作

#### std::find std::find_if std::find_if_not
- find 搜索等于 value 的元素。
- find_if 搜索谓词(一元判别式) p 为true的元素
- find_if_not 搜索谓词(一元判别式) p 为false的元素
  
find
```C++
template<typename Input,typename T>
Input find(Input first, Input last,const T& value){
    for(;first != last; ++first){
        if(*first == value){
            return first;
        }
    }
    return last;
}
```
find_if
```C++
template<typename Input,typename UnaryPredicate>
bool find_if(Input first,Input last,UnaryPredicate p){
    for(;first != last;++first){
        if(p(*first)){
            return first;
        }
    }
    return last;
}

// 例
// 能否被5整除
bool DivBy5(int x){
    return x % 5 ? true : false;
}

vector<int> vec{10,5};

auto iloc = std::find_if(vec.begin(),vec.end(),DivBy5);
```
find_if_not
```C++
template<typename Input,typename UnaryPredicate>
bool find_if(Input first,Input last,UnaryPredicate p){
    for(;first != last;++first){
        if(!p(*first)){
            return first;
        }
    }
    return last;
}
```
#### std::search
搜索[s_first, s_last)在[first, last)中首次出现

返回 searcher(first, last).first;
```C++
//example
std::string str1 = "why waste time learning, when ignorance is instantaneous?";
std::string str2 = "learning";
auto re = std::rearch(str1.begin(),str1.end(),str2.begin(),str2.end());
```
search
```C++
// 第一种 版本  ，  暴力实现
template<typename T1, typename T2>
constexpr T1 search(T1 first,T1 last, T2 s_first, T2 s_last){
    for (;;++first){
        T2 it = s_first;
        for(T2 s_it{s_first};;++it,++s_it){
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
// 第二种版本，  利用KMP 或者 BM算法
```