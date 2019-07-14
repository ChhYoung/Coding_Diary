# 栈和队列

## 1.栈

- 利用 list 实现栈

```c++
#include"list.h"
namespace DSA{

template<typename T>
class Stack:public List<T>{
public:
    void push(T const& e){ this->insert_as_last(e);}
    T pop(){ return this->remove(this->last());}
    T& top(){ return this->last()->data;}
};
}
```

- 你用 vector实现栈

```c++
#include"vector.h"
namespace DSA{

template<typename T>
class Stack:public Vector<T>{
public:
    void push(T const& e){ this->insert(e);}
    T pop(){
        T res = this->elem_[this->size_-1];
        remove(this->size_-1);
        return res;
    }
    T& top(){
        return this->elem_[this->elem_size_-1];
    }
}; 
}
```

