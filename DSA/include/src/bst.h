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

    static NodePtr searchInRev(NodePtr& v, const T& e, NodePtr& hot){
        if(!v || (e == v->data_)) { return v;}
        // 利用hot来记录 ： 
        //   查找成功时的节点的祖先节点
        //   查找失败时假想节点的祖先节点
        hot = v;
        // 返回值指向命中的节点(或 假想的哨兵)
        //    hot指向其父亲，退化时初始值为  nullptr
        return searchInRev(((e < v->data_) ? v->lChild_ : v->rChild_ ), e, hot);
    }   
    // 改写为迭代形式
    static NodePtr searchInIt(NodePtr& v, const T& e, NodePtr& hot){
        if(!v || (e == v->data_)) { return v;}
        hot = v;
        while(true){
            auto& c = (e < hot->data) ? hot->lChild_ : hot->rChild_;
            if(e == c->data_ ) return c;
            hot = c;
        }
    }

    // 查找
    virtual NodePtr& search(const T& e){
        //return searchInRev(this->root_,e,this->hot_ = nullptr);
        return searchInIt(this->root_,e,this->hot_ = nullptr);
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
            // 取等时为退化情况，即 直接后继刚好是要删除节点的右孩子
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

    // zig 顺时针旋转
    NodePtr zig(){
        NodePtr c = lChild_;
        c->parent_ = this->parent_;
        if ( c->parent_ )
            ( ( this == c->parent_->rChild_ ) ? c->parent_->rChild_ : c->parent_->lChild_ ) = c;
        lChild_ = c->rChild_;
        if ( lChild_ ) lChild_->parent_ = this;
        c->rChild_ = this; 
        this->parent_ = c;
        return c;
    }

    // zag 逆时针旋转
    NodePtr zag(){
        NodePtr c = rChild_;
        c->parent = this->parent_;
        if ( c->parent )
            ( ( this == c->parent_->lChild_ ) ? c->parent_->lChild_ : c->parent_->rChild_ ) = c;
        rChild_ = c->lChild_;
        if ( rChild_ ) rChild_->parent_ = this;
        c->lChild_ = this; 
        this->parent_ = c;
        return c;
    }


    /* 
    // zig 操作
    //  返回旋转后原位置节点的指针
    NodePtr zig(NodePtr& v){
        auto c = v->lChild_;
        // c 为空则什么也不做
        if(c == nullptr) { return v; }
        c->parent_ = v->parent_;
        if(v->parent_){
            v->isLChild() ? v->parent_->lChild_ = c : v->parent_->rChild_ = c;
        }
        v->parent_ = c;
        v->lChild_ = c->rChild_;
        c->rChild_ = v;
        // 更新高度
        this->updateHeightAbove(v);
        return c;
    }
    
    void zig(){
        auto c = this->lChild_;
        // c 为空则什么也不做
        if(c == nullptr) { return ; }
        c->parent_ = this->parent_;
        if(this->parent_){
            this->isLChild() ? this->parent_->lChild_ = c : this->parent_->rChild_ = c;
        }
        this->parent_ = c;
        this->lChild_ = c->rChild_;
        c->rChild_ = this;
        this->updateHeightAbove(v);
    }

    // zag 
    //  返回旋转后原位置节点的指针
    NodePtr zag(NodePtr& v){
        auto c = v->rChild_;
        // c 为空则什么也不做
        if(c == nullptr) { return v; }
        c->parent_ = v->parent_;
        if(v->parent_){
            v->isLChild() ? v->parent_->lChild_ = c : v->parent_->rChild_ = c;
        }
        v->parent_ = c;
        v->rChild_ = c->lChild_;
        c->lChild_ = v;
        this->updateHeightAbove(v);

        return c;
    }

    void zag(){
        auto c = this->rChild_;
        // c 为空则什么也不做
        if(c == nullptr) { return ; }
        c->parent_ = this->parent_;
        if(this->parent_){
            this->isLChild() ? this->parent_->lChild_ = c : this->parent_->rChild_ = c;
        }
        this->parent_ = c;
        this->rChild_ = c->lChild_;
        c->lChild_ = this;
        this->updateHeightAbove(v);
    }
    */

    //   通过zag旋转将，子树x拉伸为最左侧通路
    void stretchByZag(NodePtr& x){
        int h = 0;
        NodePtr p=x;
        // 最右节点，p为拉伸后的根节点
        while(p->rChild_){
            p = p->rChild;
        }
        // 转到最左侧通路的末端
        while(x->lChild_){
            x = x->lChild_;
        }
        x->height_ = h++;
        // 若右子树为空，则上一层，否则反复地以x为轴旋转
        // 直到到达p
        for( ; x != p; x = x->parent_, x->height = h++){
            while(x->rChild_)
                x->zag();
        }
    }

};

}
#endif // _DSA_INCLUDE_SRC_GRAPH_H__
