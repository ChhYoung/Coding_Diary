// splay tree 伸展树

#ifndef _DSA_INCLUDE_SRC_SPLAY_H__
#define _DSA_INCLUDE_SRC_SPLAY_H__

#include"bst.h"
#include"release.h"

namespace DSA{

// 伸展树
// 基于局部性原理：
//      每次访问后将当前节点提升到树根
template<typename T> 
class Splay : public BST<T> {
public: 
    typedef BinNode<T> Node;
    typedef Node* NodePtr;
protected:
    // 伸展树算法的核心：从节点v开始向上层做双层伸展
    // * 区别： 单层伸展操作是从当前层开始每次只考虑当前层，只考虑当前v的父亲节点p，
    //          先对p旋转，v的父节点又变成g，此时考虑父节点g ...
    //          逐层地进行旋转，在最坏情况下单次的均摊复杂度  O(n)
    //          双层拓展则同时考虑两层： 先对g进行旋转，再旋转p，
    // * 优点： 对于 zig-zig  zag-zag的情况，使用双层伸缩能够使对应的分支
    //          的高度呈几何级数(大致减半)的速度收缩。 单次操作的均摊复杂度
    //          不超过  O(log n)
    NodePtr splay(NodePtr v){
        // 平凡情况
        if(!v) { return nullptr;}
        // 定义父节点p, 爷爷节点g
        NodePtr p,g;

        // 自下而上反复做双层伸展
        while((p = v->parent_ ) && (g = p->parent_)){
            // 每次迭代后v都成为原祖父的父亲 ( great grand parent )
            auto gg = g->parent_;
            // 按照zig-zag   zag-zig  zig-zig   zag-zag 这四种情况来处理
            // 按照 3+4 重构的实现方法
            if(v->isLChild()){
                // zig-zig                
                //           g              v
                //      p           --->        p
                //  v                               g
                if(p->isLChild()){
                    // p->rChild_ 作为 g 的左孩子接入 
                    g->attachAsLChild(p->rChild_);
                    p->attachAsLChild(v->rChild_);
                    p->attachAsRChild(g);
                    v->attachAsRChild(p);
                }
                // zig-zag
                //  g                           v
                //          p ---->         g       p
                //      v
                else {
                    g->attachAsRChild(v->lChild_);
                    p->attachAsLChild(v->rChild_);
                    v->attachAsLChild(g);
                    v->attachAsRChild(p);
                }
            }
            else{
                // zag-zag
                // g                                v    
                //      p           ---->       p 
                //          v               g
                if(p->isRChild()){
                    g->attachAsRChild(p->lChild_);
                    p->attachAsRChild(v->lChild_);    
                    p->attachAsLChild(g);
                    v->attachAsLChild(p);
                }
                // zag-zig
                //              g               v
                //      p           ---->    p      g
                //          v
                else{
                    p->attachAsRChild(v->lChild_);
                    g->attachAsRChild(v->rChild_);
                    v->attachAsLChild(p);
                    v->attachAsRChild(g);
                }
            }
            // 再处理曾祖父的情况
            if(!gg){
                v->parent_ = nullptr;
            }
            else{
                (g == g->lChild_) ? gg->attachAsLChild(v) : gg->attachAsRChild(v);
            }

            this->updateHeight(g);
            this->updateHeight(p);
            this->updateHeight(v);
        }// 循环结束时， g == nullptr , p可能为非空

        // 如果p是根，只需一次额外的单旋
        if(p = v->parent_){
            // zig
            if(v == p->lChild_){
                p->attachAsLChild(v->rChild_);
                v->attachAsRChild(p);
            }
            // zag
            else{
                p->attachAsRChild(v->lChild_);
                v->attachAsLChild(p);
            }

            this->updateHeight(p);
            this->updateHeight(v);
        }

        // 伸展完成，返回树根
        v->parent_ = nullptr;
        return v;
    }

public:
    // 查找
    virtual NodePtr& search(const T& e) override{
        //  调用 BST的内部接口定位目标节点
        auto p = this->searchInIt(this->root_, e, this->hot_ = nullptr);
        //  无论成功与否，最后被访问的节点都将伸展到根
        this->root = splay(p ? p : this->hot_);
        // 总是返回根节点
        return this->root_;
    }   

    // 插入
    virtual NodePtr insert(const T& e) override{
        // 处理原树为空树的退化情况
        if( !this->root_){
            ++this->size_;
            return this->root_ = new Node(e);
        }

        // 处理节点已经存在的情况
        // 查找时已经伸展，直接返回
        //      其中隐含了将 查找失败时将接近的节点更新为父节点
        if( e == search(e)->data_){    
            return this->root_;
        }

        // 查找失败的情况
        ++this->size_;
        auto t = this->root_;
        //  图 8.8 
        if(this->root_->data_ < e){
            // 插入新根节点，以t t->rChild_ 为左右孩子
            // 即t 即 t的左子树为  v的左子树
            //    t的右子树为v的右子树
            //      t 的右孩子置空
            this->root_ = new Node(e, nullptr, t, t->rChild_);
            t->parent_ = this->root_;
            if(t->rChild_){
                t->rChild_->parent_ = this->root_;
                t->rChild_ = nullptr;
            }
        }
        else{
            this->root_ = new Node(e, nullptr, t->lChild, t);
            t->parent_ = this->root_;
            if(t->lChild_){
                t->lChild_->parent_ = this->root_;
                t->lChild_ = nullptr;
            }
        }

        // 更新t及其祖先的高度
        this->updateHeightAbove(t);
        return this->root_;
    }     

    // 删除 
    bool remove(const T& e) override{
        // 树为空或者目标不存在则无法删除
        if( !this->root_ || e != search(e)->data_){
            return false;
        }

        // 经过search 后节点e已经被伸展到树根
        auto t = this->root_;

        // 无左子树，直接删除
        if(!this->root_->hasLChild()){
            // 右子树为树根
            this->root_ = this->root_->rChild_;
            // 更新右子树父亲节点为null
            if(this->root_) {
                this->root_->parent_ = nullptr;
            }
        }

        // 无右子树，直接删除
        else if(!this->root_->hasRChild()){
            this->root_ = this->root_->lChild_;
            if(this->root_){
                this->root_->parent_ = nullptr;
            }
        }

        // 左右子树同时存在
        else {
            // 暂时切除左子树
            // ltree 保存左子树节点指针
            auto ltree = this->root_->lChild_;
            ltree->parent_ = nullptr;
            this->root_->lChild_ = nullptr;

            // 只保留右子树
            this->root_ = this->root_->rChild_;
            this->root_->parent_ = nullptr;

            // 以原树根为目标，做一次(必定失败的)查找
            search(t->data_);

            // 自此，右子树中最小节点必定伸展到根，且(因无雷同节点)其左子树必空，
            // 于是只需将隔离的原左子树接回原为即可
            this->root_->lChild_ = ltree;
            ltree->parent_ = this->root_;
        }
        
        // 释放节点，更新规模
        release(t->data_);
        release(t);
        this->size_--;

        // 此后，若树非空，则树根的高度需要更新
        if(this->root_){
            this->updateHeight(this->root_);
        }

        return true;
    }
};



}


#endif //  _DSA_INCLUDE_SRC_SPLAY_H__