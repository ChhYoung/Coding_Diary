#pragma once

#ifndef _DSA_INCLUDE_SRC_LIST_H__
#define _DSA_INCLUDE_SRC_LIST_H__

#include<assert.h>
#include"swap.h"
#include"list_node.h"
#include<stdlib.h> // rand()

namespace  DSA
{

template<typename T>
class List{
    using Node =  ListNode<T>; 
    using NodePtr = Node*;
private: 
// 数据成员 
    // 规模
    int size_ = 0;
    // 头部哨兵
    NodePtr header = nullptr;
    // 尾部哨兵
    NodePtr trailer = nullptr;
public: 
// 构造函数
    List(){ init();}        


};


} // namespace  DSA
#endif // _DSA_INCLUDE_SRC_LIST_H__