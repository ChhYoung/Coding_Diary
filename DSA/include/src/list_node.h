//#pragma once

#ifndef _DSA_INCLUDE_SRC_LIST_NODE_H__
#define _DSA_INCLUDE_SRC_LIST_NODE_H__

namespace  DSA
{
// 秩    
using Rank = int;
// 链表节点
template<typename T>
struct ListNode{
    // 定义节点及节点指针的简洁命名
    
    using Node = ListNode<T>;
    using Ptr = Node*;
    /*
    typedef ListNode<T> Node ;
    typedef Node* Ptr;*/
// members
    // 数据
    T data;
    // 前驱
    Ptr pred;
    // 后继
    Ptr succ;
// 构造函数
    ListNode():data(),pred(nullptr),succ(nullptr){}
    ListNode(T e,Ptr p=nullptr,Ptr s=nullptr)
            :data(e),pred(p),succ(s)
            {}
// 操作接口            
    // 插入一个节点作为当前节点的前驱
    // 返回该插入的节点
    Ptr insert_as_pred(T const& e){
        auto node = new Node(e,pred,this);
        if(pred){
            pred->succ = node;
        }
        pred = node;
        return node;
    }         
    // 插入一个节点作为当前节点的后继
    // 返回该插入的节点
    Ptr insert_as_succ(T const& e){
        auto node = new Node(e,this,succ);
        if(succ){
            succ->pred = node;
        }
        succ = node;
        return node;
    }      
}; // ListNode
} // namespace  DSA
#endif // _DSA_INCLUDE_SRC_LIST_NODE_H__