// red black tree

#ifndef _DSA_INCLUDE_SRC_RBTREE_H__
#define _DSA_INCLUDE_SRC_RBTREE_H__

#include"bst.h"

namespace DSA{

// 红黑树：
// * 一种适度平衡的树：相比AVL树而言，每次插入删除后对树的拓扑结构的变化
//      不超过 O(1), 任意左右子树的高度不相差两倍
// * 通过颜色来动态调整
// * 将红节点上升当父亲黑节点同位置高度后，等价为  4阶B树  [2,4]-树 
// * 红黑树满足以下4个条件：
//      * 树根为黑色
//      * 外部节点均为黑色
//      * 其余节点若为红色，则其孩子节点必为黑色   ---> 红孩子的父亲孩子节点都为黑
//      * 任意外部节点到根节点的途径中，黑色节点的数量相同 ---> 控制深度
template <typename T>
class RBTree : public: BST<T>{
public:
    typedef BindNode<T> Node;
    typedef Node*  NodePtr;
    
    // 插入重写
    virtual NodePtr insert(const T& e) override{
        auto& x = this->search(e);
        // 若存在
        if(x) { return x;}
        // 不存在，则插入
        // 设插入刚插入的节点 都是红色
        x = new Node(e,this->hot_,nullptr,nullptr,-1,RBColor::RB_RED);
        // 双红修正
        solveDoubleRed(x);
        return x ? x : this->hot_->parent_;
    }

    // 删除重写
    // 删除重写分为三种情况：
    // *  情况一： 删除节点为 红节点，则删除后只需将一个黑孩子替换到原来位置
    //             即可，
    // *  情况二： 删除节点是黑节点，有红色的孩子，则将红孩子替换到原来位置
    //             然后染黑即可
    // *  情况三： 删除节点是黑节点， 孩子都是黑色，删除后局部子树的高度降低
    //             此时要双黑修正
    virtual bool remove(const& T e) override {
        auto& x = this->search(e);
        if(x) { return  false;}
        auto r = this->removeAt(x,this->hot_);
        //删除后树为空，直接返回
        if(!(--this->size_)) { return  true;}
        // 被删除节点的父亲 hot_
        // 若被删除的是根节点，则将根现在的根节点置黑，并更新黑高度
        if(!this->hot_){
            this->root_->color_ = RBColor::RB_BLACK;
            this->updateHeight(this->root_);
            return true;
        }
        // 若所有祖先的黑高度依然平衡，则无需调整
        if(blackHeightUpdated(this->hot_)){ return true;}
        // 否则，若r为红色，则直接染色 (情况二)
        if(isRed(r)){
            r->color_ = RBColor::RB_RB_BLACK;
            r->height_ ++;
            return ture;
        }
        // 情况三:双黑修正
        solveDoubleBalck(r);
        return true;
    }

protected:
    /*  双红修正: 节点x与其父都是红色,分为两大类情况
        RR-1: 2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
        RR-2: 3次颜色翻转，3次黑高度更新，0次旋转，需要递归
        
        - RR-1：g的另外一个孩子u为黑色
            
                [g]                  [g]            等
            <p>     [u]       <p>          [u]
        <x>                       <x>
        则可直接通过 3+4重构， 对 x p g 重构，然后[a,b,c] 中b染成黑，ac染成红色

        - RR-2: g的两个孩子都是红色
            [g]               [g]
        <p>     <u>     <p>         <u>  等
    <x>                     <x>

        通过4 5 重构将4个节点先合并，[a,b,c,d] 后按照B-树，上溢来分裂
        将x,g 染红， p,u 染黑 即可，但由于c(g)将上升到高层节点，所以
        上层也要检查颜色(B-树的上溢传播)
    */
    void solveDoubleRed(NodePtr x){
       //此时x必为红
       // 若此时已经递归到树根,则将其转黑，树的高度也递增
        if(x->isRoot()){ 
           this->root_->color_ = RBColor::RB_BLACK;
           this->root_->height_ ++;
           return ;
        }
        // 否则 x 的父亲存在
        // 若p为黑，则可以终止
        auto p = x->parent_;
        if(isBlack(p)) { return ;}
        // p为红，则x祖父必然存在，且为黑色
        auto g = p->parent_;
        // 叔叔节点
        auto u = x->uncle();
        // u为黑色 或nullptr， RR-1
        if(isBlack(u)){
            // x p g同侧
            // zig-zig zag-zag
            if(x->isLChild() == p->isLChild()){
                // p 变为黑色
                p->color_ = RBColor::RB_BLACK;
            }
            // x p 异侧 
            // zig-zag zag-zig
            else{
                // x 变黑
                x->color_ = RBColor::RB_BLACK;
            }
            // g 必变红
            g->color_ = RBColor::RB_RED;

            // 与上一层相连接
            // 曾祖父
            auto gg = g->parent_;
            // 调整后的子树根节点
            auto r = this->fromParentTo(g) = this->rotateAt(x);
            r->parent_ = gg;
        }
        // u 为红色 RR-2
        else{
            // p 染黑
            p->color_ = RBColor::RB_BLACK;
            // u 染黑
            u->color_ = RBColor::RB_BLACK;
            // g非根，则染红
            if(!g->isRoot()){
                g->color_ = RBColor::RB_RED;
            }
            // 上溯
            solveDoubleRed(g);
        }
    }

    /* 双黑修正: 双黑修正分为3种情况

    *	BB-1 ：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
	*	BB-2-R：2次颜色翻转，2次黑高度更新，0次旋转，不再递归
	*	BB-2-B：1次颜色翻转，1次黑高度更新，0次旋转，需要递归
	*	BB-3 ：2次颜色翻转，2次黑高度更新，1次旋转，转为BB-1或BB2R
    
    s 为 x 的兄弟节点; 
    - BB-1 ：s为黑，且有 红孩子--> 对应B树下溢操作时兄弟节点有多余key
            p                    [ , p ,]
        [s]       x           [t,s]       []
    <t>           r                       [r]

            s                   [ ,s, ]
        t       p             [t]       [p]
                r                       [r]

    - BB-2-R : s为黑，无 红孩子, p 为红色时, 对应b树的不足合并
        <p>                [,p,]
    [s]     [x]       [s]       []
            [r]                 [r]

                            []
                            [s,p]
    此时只要将s变红，p变黑即可

    - BB-2-B : s为黑，s有红孩子, p 为黑色
    令s变红， 但此时树的黑深度减少1，所以要上溯

    - BB-3 : s 为红，则经旋转后，r的兄弟变为rc，rc为黑，p为红，有rc的孩子节点颜色
            可以转换成BB-1 或者 BB-2-R 来处理情况
            s为子树根并染黑，p染红，则又转换成BB-2-R 或BB-1
            p                       [s,p]
        s       x  -------->    l     rc     [x]
      l   rc    r                            [r]

        s                           [s,p]
    l       p                   l   rc   [x]
        rc      x -------->             [r]
                r
     */
    void solveDoubleBlack(NodePtr r){
        // r 的父亲
        auto p = r ? r->parent_ : this->hot_; if(!p) { return ;}
        // r 的兄弟
        auto s = r->sibling();

        // s为黑
        if(isBlack(s)){
            // s 的红孩子 (若左、右孩子皆红，左者优先；皆黑时为NULL)
            auto t = isRed(s->lChild_) ? s->lChild_ : (isRed(s->rChild_) ? s->rChild_ : nullptr);
            // BB-1 有红孩子
            if(t){
                // 备份原子树根节点p颜色，并对其父亲，祖父通过旋转重平衡
                //  并将左右孩子染黑
                auto oldColor = p->color_;
                // 旋转
                auto b = this->fromParentTo(p) = this->rotateAt(t);
                if(b->lChild_) {
                    b->lChild_->color = RBColor::RB_BLACK;
                    this->updateHeight(b->lChild_);
                }
                if(b->rChild_) {
                    b->rChild_->color = RBColor::RB_BLACK;
                    this->updateHeight(b->rChild_);
                }
                b->color_ = oldColor;
                this->updateHeight(pb;
            }
            else{
                // 无红孩子          
                // s染红
                s->color_ = RBColor::RB_RED;
                s->height_ --;
                // BB-2R
                if(isRed(p)){
                    p->color_ = RBColor::RB_BLACK;
                }
                // BB-2B
                else{
                    p->height_ --;
                    solveDoubleBlack(p);
                }
            }
        }
        // BB-3 ： s 为红
        else{
            // s 转黑，p转红
            s->color_ = RBColor::RB_BLACK;
            p->color_ = RBColor::RB_RED;
            // 取t与其父s同侧
            auto t = s->isLChild() ? s->lChild_ : s->rChild_;
            this->hot_ = p;
            this->fromParentTo(p) = this->rotateAt(t);
            solveDoubleBlack(r);   
        }
    }

};



}
#endif // _DSA_INCLUDE_SRC_RBTREE_H__