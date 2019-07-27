// binary search tree
#ifndef _DSA_INCLUDE_SRC_BST_H__
#define _DSA_INCLUDE_SRC_BST_H__

#include"BinTree.h"
#include"swap.h"
#include"release.h"


namespace DSA{

// 词条模板类
template<typename K, typename V>
struct  Entry{
    // 关键码
    K key;
    // 数值
    V value;
    // 词条类型定义
    typedef Entry<K,V> EntryType;
    // 默认构造函数
    Entry(K k=K(),V v=V())
        : key(k)
        , value(v)
    {}
    // 基于克隆的构造函数
    Entry(EntryType const& e)
        : key(e.key)
        , value(e.value)
    {}
    // 重载操作符
    bool operator <  (const EntryType & e){ return key < e.key;}
    bool operator >  (const EntryType & e){ return key > e.key;}
    bool operator == (const EntryType & e){ return key == e.key;}
    bool operator != (const EntryType & e){ return key != e.key;}
};

template<typename T> 
class BST : public BinTree<T> {
public: 
    typedef BinNode<T> Node;
    typedef Node* NodePtr;

    static NodePtr searchIn(NodePtr& v, const T& e, NodePtr& hot){
        if(!v || (e == v->data_)) { return v;}
        // 利用hot来记录 ： 
        //   查找成功时的节点的祖先节点
        //   查找失败时假想节点的祖先节点
        hot = v;
        // 返回值指向命中的节点(或 假想的哨兵)
        //    hot指向其父亲，退化时初始值为  nullptr
        return searchIn(((e < v->data_)?v->lChild_:v->rChild_),e,hot);
    }   

    // 查找
    virtual NodePtr& search(const T& e){
        return searchIn(this->root_,e,this->hot_ = nullptr);
    }

    // 插入
    virtual NodePtr insert(const T& e){
        auto& x = search(e);
        if(!x){
            x = new Node(e, this->hot_);
            ++ this->size_;
            this->updateHeightAbove(x);
        }
        return x;
    }
    // 删除分为两类情况：
    // - 单分支情况：  被删除节点的左/右孩子为空，直接删除节点，由左/右孩子来替换该节点
    // - 多分支情况：  被删除节点左右孩子都存在， 将节点值与节点的直接后继互换，由于直接
    //                 后继最多只有一个右孩子，则转换成单分支情况

    static NodePtr removeAt(NodePtr& x, NodePtr& hot){
        // 实际被摘除的节点，初始值同x
        NodePtr w = x; 
        // 实际被摘除节点位置的接替者
        NodePtr succ = nullptr;
        // 左子树为空
        if( !x->lChild_){
            succ = x = x->rChild_;
        }
        // 右子树为空
        else if(!x->rChild_){
            succ = x = x->lChild_;
        }
        // 双分支情况
        else{
            // 找到直接后继
            w = w->succ;
            // 交换数据
            swap(x->data_, w->data_);
            // u 实际删除节点的父亲节点
            auto u = w->parent_;
            // 取等时为退化情况，即 直接后继刚好时要删除节点的右孩子
            (u == x? u->rChild_ : u->lChild_) = succ = w->rChild_;
        }

        // 记录实际被删除节点的父亲
        hot = w->parent_;
        // 将实际被删除节点的接替者与 hot 关联
        if(succ){ succ->parent_ = hot;}
        // 释放实际被删除节点
        release(w->data_);
        release(w);
        return succ;
    }

    // 删除
    virtual bool remove(const T& e){
        auto& x = search(e);
        if(!x){return false;}
        removeAt(x,this->hot_);
        --this->size_;
        this->updateHeightAbove(x);
        return true;
    }

protected: 
    // 命中节点的父亲
    NodePtr hot_;
    // 3+4 重构
    // 找到最低的失衡节点g
    // 直接将 g p v (a,b,c) T0,T1,T2,T3 按照中序遍历的关系排列后构成
    // 一颗子树，该树也刚好是AVL树
    // ---重构后子树与上层的链接由上层调用者完成
    NodePtr connect34(NodePtr a,NodePtr b,NodePtr c,
                        NodePtr t0,NodePtr t1,NodePtr t2,NodePtr t3){
        a->lChild_ = t0; if(t0) { t0->parent_ = a;}
        a->rChild_ = t1; if(t1) { t1->parent_ = a;}
        this->updateHeight(a);

        c->lChild_ = t2; if(t2) { t2->parent_ = c;}
        c->rChild_ = t3; if(t3) { t3->parent_ = c;}
        this->updateHeight(c);

        b->lChild_ = a; a->parent_ = b;
        b->rChild_ = c; c->parent_ = b;
        this->updateHeight(b);

        // 该子树新的根节点
        return b; 
    }

    // 旋转调整
    // 根据 g p v的位置来旋转子树(利用3+4 重构来完成旋转)
    NodePtr rotateAt(NodePtr v){
        NodePtr p = v->parent_;
        NodePtr g = p->parent_;
        // zig
        if(p->isLChild()){
            // zig-zig 如图 7.17
            if(v->isLChild()){
                // 子树与上层调用者的链接
                p->parent_ = g->parent_;
                return connect34(v,p,g,
                    v->lChild_,v->rChild_,p->rChild_,g->rChild_)
            }
            // zig-zag 7.18
            else{
                v->parent_ = g->parent_;
                return connect34(p,v,g,
                    p->lChild_, v->lChild_,p->rChild_,g->rChild_);
            }
        }
        // zag
        else {
            // zag-zag
            if(v->isRChild()){
                p->parent_ = g->parent_;
                // 对称操作
                return connect34(g,p,v,
                    g->lChild_,p->lChild_,v->rChild_,v->rChild_);
            }
            // zag-zig
            else{
                v->parent_ = g->parent_;
                return connect34(g,v,p,
                    g->lChild_,v->lChild_,v->rChild_,p->rChild_);
            }
        }
    }
};

}
#endif // _DSA_INCLUDE_SRC_GRAPH_H__
