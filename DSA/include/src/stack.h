//#pragma once
#ifndef _DSA_INCLUDE_SRC_STACK_H__
#define _DSA_INCLUDE_SRC_STACK_H__

//#pragma once
/* 
#include "list.h"

namespace DSA 
{

//! 栈
// list实现的栈
template <typename T> 
class Stack : public List<T>
{
public:
	void push(T const& e) { this->insert_as_last(e); }
	T pop() { return this->remove(this->last()); }
	T& top() { return this->last()->data; }
};

}
*/

#include"vector.h"
namespace DSA{

template<typename T>
class Stack:public Vector<T>{
public:
    
    void push(T const& e){ this->insert(e);}
    T pop(){
        T res = this->elem_[this->size_-1];
        this->remove(this->size_-1);
        return res;
    }
    T& top(){
        return this->elem_[this->size_-1];
    }
}; 
}


#endif // _DSA_INCLUDE_SRC_STACK_H__