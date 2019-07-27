#ifndef _DSA_INCLUDE_SRC_AVL_H__
#define _DSA_INCLUDE_SRC_AVL_H__

#include"bst.h"

namespace DSA{

template<typename T> 
class AVL: public BST<T> {
public: 
    typedef BinNode<T> Node;
    typedef Node* NodePtr;

    virtual NodePtr insert(T const& e) override {
        auto& x = this->search(e);
        if(x){ return x;}

        // 目标节点不存在则创建新节点
        x = new Node(e,this->hot_);
        this->size_++;
        auto xx = x;
        // 此时 x的父亲 hot_ 若增高，   其祖父可能会失衡
        // 从x的父亲节点逐层向上，依次检查各代祖先g
        for(auto g = x->parent_; g; g = g->parent_){
            if(!)
        }

    }

};

} // namespace DSA

#endif // _DSA_INCLUDE_SRC_AVL_H__