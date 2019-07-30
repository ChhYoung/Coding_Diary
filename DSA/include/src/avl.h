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

        // 目标节点不存在则以hot_为父节点创建新节点,
        x = new Node(e,this->hot_);
        this->size_++;
        auto xx = x;

        // 此时 x的父亲 hot_ 若增高，   其祖父可能会失衡
        // 从x的父亲节点逐层向上，依次检查各代祖先g
        for(NodePtr g = x->parent_; g; g = g->parent_){
            // 一旦发现g失衡,则通过调整恢复平衡
            if(!avlBalanced(g)){
                this->fromParentTo(g) = this->rotateAt(tallerChilkid(tallerChild(g)));
                // g 恢复平衡后局部子树高度必然恢复，其祖先也如此，故调整结束
                break;
            }
            else{
                // 平衡性不变，但高度却可能改变
                this->updateHeight(g);
            }
        }
        return xx;
    }

    virtual bool remove(T const& e) override{
        auto& x = this->search(e);
        if(!x) { return false;}
        // 按照BST规则删除后，hot_及其祖先均有可能失衡
        this->removeAt(x,this->hot_);
        --this->size_;

        // 从 hot_ (被删除节点父亲出发)，依次检查各代祖先g
        for(auto g=this->hot_; g; g = g->parent_){
            if(!avlBalanced(g)){
                g = this->fromParentTo(g) = this->rotateAt(tallerChild(tallerChild(g)));
            }
            this->updateHeight(g);
        }
        // 可能需做过Ω(log n)次调整；无论是否做过调整，全树高度均可能下降
        return true;
    }

};

} // namespace DSA

#endif // _DSA_INCLUDE_SRC_AVL_H__