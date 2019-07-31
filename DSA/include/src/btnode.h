// b-tree node
#ifndef _DSA_INCLUDE_SRC_BTNODE_H__
#define _DSA_INCLUDE_SRC_BTNODE_H__

#include"vector.h"

namespace DSA{

// B树节点
template<typename T> 
struct BTNode{
    typedef BTNode<T*> Ptr;
    
    // 父节点 
    Ptr parent_;
    // 关键码
    Vector<Ptr> key_;
    // 孩子(长度总比 key 多 1 )

    BTNode(){ 
        parent_ = nullptr;
        child_.insert(0,nullptr);
    }

    BTNode(T const& e, Ptr lc = nullptr, Ptr rc = nullptr){
        parent_ = nullptr;
        key_.insert(0,e);
        child_.insert(0,lc);
        child_.insert(1.rc);
        if(lc) { lc->parent_ = this;}
        if(rc) { rc->parent_ = this;}
    }
};

} // namespace  DSA
#endif //  _DSA_INCLUDE_SRC_BTNODE_H__
