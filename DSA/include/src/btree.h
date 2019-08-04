// b-tree
#ifndef _DSA_INCLUDE_SRC_BTREE_H__
#define _DSA_INCLUDE_SRC_BTREE_H__

#include"btnode.h"
#include"release.h"

namespace DSA{

/*
- B 树： 对于外部存储器如磁盘之类，其读取数据是按批读取，
        所以读一组数据与单个数据没有区别，采用矮宽的多路搜索树
        减少I/O 操作数
- N个节点， m阶
- 高度：  h = θ(logm N); 是BST高度的 1/ [ (log2 M) -1 ]
- 每个节点的分支数：树根>=2, 其他则 [ ceil(m/2) , m ]
- 每个节点的关键码数：分支数-1，即 [ ceil(m/2)-1 , m-1 ]
 */
template<typename T> 
class BTree{
public:
    typedef BTNode<T> Node;
    typedef Node* NodePtr;


protected:
    // 关键码总数
    int N_;
    // B-树阶数，至少为3， 创建时指定，一般不了修改
    int m_;
    // 根节点
    NodePtr root_;
    // search 最后访问非空节点的位置
    NodePtr hot_;    

protected:
    // 因插入而上溢之后的分裂处理
    //  当节点的关键码 为 m 个， 有m+1个分支时
    // 将m个关键码以中位数s为轴(上升到上一层节点中)，[0,s) 为左侧，[s+1,m-1]为右侧 (m-s-1)个关键码，m-s个child_
    void solveOverflow(NodePtr node){
        // 递归基：当前节点并未上溢
        if(node->child_.size() < m_) {
            return ;
        }
        // 轴点
        auto s = m_ / 2;
        // 注意新节点已经有一空孩子
        auto u  = new Node();
        // 右侧的  m-s-1 个孩子及关键码分裂成右侧节点 u
        // 从 s+1 开始不断将关键码移入新节点中
        for( Rank i = 0; i < m_-s-1; ++i){
            u->child_.insert(i, node->child_.remove(s+1));
            u->key_.insert(i,node->key_.remove(s+1));
        }
        // 由于孩子数比key数量多1,移动 node 最靠右的孩子
        u->child_[m_-s-1] = node->child_.remove(s+1);
        // 若u的孩子们非空
        // 孩子们的父亲节点同一指向 u
        if(u->child_[0]){
            for(Rank i=0; i < m_ - s; ++i){
                u->child_[i]->parent_ = u;
            }
        }
        // v 当前的父亲节点 p 
        auto p = node->parent_;
        // p 为空则创建, 这是唯一可以使B树高度增加的操作,上溢到根节点
        if(!p){
            root_ = p =new Node();
            p->child_[0] = node;
            node->parent_ = p;
        }
        // 在父亲节点中找到 key 上升后插入的位置
        auto r = 1 + p->key_.search(node->key_[0]);
        // 上升插入v->key, 及其新节点 u 
        p->key_.insert(r, node->key_.remove(s));
        p->child_.insert(r+1,u);
        // 新右节点链接到父亲
        u->parent_ = p;
        // 递归检查上层节点
        solveOverflow(p);
    }


    // 因删除而下溢后的旋转合并
    // 下溢:
    // 可以分为三种情况
    // - 1 : 旋转操作， v的左兄弟L存在且 key数量>= ceil[m/2] (即上移L的一个key后不会发生下溢)
    //          将L的最大key上移， p的合适的key下移v中
    // - 2 : V的右兄弟存在在,同上
    // - 3 : 无论左右都不够 (一个含有 ceil[m/2]-1 个key)，则下移p的合适key， 左右合并
    void solveUnderflow(NodePtr node){
        // 递归基, 不满足下溢条件
        if((m_ + 1)/2 <= node->child_.size()) { return ;}
        auto p = node->parent_;
        // 递归基，下溢到根节点
        if(!p) {
            // 树根 v 不含关键码， 且有唯一的孩子
            if(node->key_.empty() && node->child_[0]){
                root_ = node->child_[0];
                root_->parent_ = nullptr;
                node->child_[0] = nullptr;
            }// 树高降低一层
            return;
        }
        // v是p的孩子，但v可能已经不含关键码，所以不能通过 关键码查找
        // 确定节点v是p的第几个孩子
        Rank r = 0;
        while(p->child_[r] != node){
            r++;
        }
        // 情况一：向左兄弟借
        // 若node不是p的第一个孩子
        if(0 < r){
            // 左兄弟
            auto ls = p->child_[r - 1];
            // 若左兄数量够大
            if( (m_+1)/2 < ls->child_.size()){
                //旋转
                // 向p接一个
                node->key_.insert(0,p->key_[r-1]);
                // ls的最大转到p
                p->key_[r-1] = ls->key_.remove(ls->key_.size()-1);
                // ls最右侧value转给 v 的最左侧
                node->child_.insert(0,ls->child_.remove(ls->child_.size()-1);
                if(node->child_[0]){
                    node->child_[0]->parent_ = node;
                }
                return ;
            }
        }
        // 情况二： 向右兄弟借
        // node 不是 p 的最后一孩子,则右兄弟必然存在
        if(r < p->child_.size()-1){
            auto rs = p->child_[r+1];
            // 数量足够大
            if((m_1+1)/2 < rs->child_.size()){
                // 向   p 借一个
                node->key_.insert(node->key_.size(),p->key_[r]);
                // rs 的最小关键码转入
                p->key_[r] = rs->key_.reomve(0);
                // rs的最左孩子转移给v的最右
                node->child_.insert(node->child_.size(),rs->child_.remove(0));
                if(node->child_[node->child_.size()-1]){
                    node->child_[node->child_.size()-1]->parent_ =  node;
                }
                return ;
            }
        }

        // 情况三： 左右为空(不同时为空)，或者太瘦
        // 与左兄弟合并
        if(0 < r){
            auto ls = p->child_[r - 1];
            // p的第r个关键码转入ls的最右，v不再是p的第r个孩子
            ls->key_.insert(ls->key_.size(),p->key_.remove(r-1));
            p->child_.remove(r);
            // v的左孩子作为ls的最右孩子
            ls->child_.insert(ls->child_.size(), node->child_.remove(0));
            if(ls->child_[ls->child_.size()-1]){
                ls->child_[ls->child_.size()-1]->parent_ = ls;
            }
            // 转移v剩余的关键码与孩子到ls中
            while(!node->key_.empty()){
                ls->key_.insert(ls->key_.size(),node->key_.remove(0));
                ls->child_.insert(ls->child_.size(),node->child_.remove(0));
                if(ls->child_[ls->child_.size()-1]){
                    ls->child_[ls->child_.size()-1]->parent_ = ls;
                }
            }
            relase(node);
        }
        // 与右兄弟合并
        else{
            auto rs = p->child_[r+1];
            rs->key_.insert(0,p->key_.remove(r));
            p->child_.remove(r);
            // p 的第r个关键码转入rs，node不再是p的第r个孩子
            // v的右孩子作为rs的最左孩子
            rs->child_.insert(0,node->child_.remove(node->child_.size()-1));
            if (rs->child_[0]) { rs->child_[0].parent = rs; }
            // 转移v剩余的关键码与孩子到rs中
            while(!node->key_.empty()){
                rs->key_.insert(0,node->key_.remove(node->key_.size()-1));
                rs->child_.insert(0,node->child_.remove(node->child_.size()-1));
                if(rs->child_[0]){
                    rs->child_[0]->parent_ = rs;
                }
            }
            relase(node);
        }
        
        // 上升一层
        solveUnderflow(p);
        return ;
    }

public: 
    BTree(int order = 3) : m_(order),N_(0) { root_ = new Node();}
    ~BTree() {if(root_){ release(root_);} } 

    // 阶数
    int order() const {return m_ ;}
    // 规模
    int size() const { return N_ ;}
    // 树根
    NodePtr& root(){ return root_;}
    // 判空
    bool empty() const { return !root_;}

    // 查找
    NodePtr search(const T& e){
        // 从根节点出发
        auto v = root_;
        hot_ = nullptr;
        // 逐层查找
        while(v){
            // 在当前节点，找到不大于e的最大关键码
            auto r = v->key_.search(e);
            // 查找成功
            if((0 <= r) &&  ( e == v->key_[r])) return v;
            // 否则转入对应的子树,  hot_指向其父，需要一次I/O，最费时间
            hot_ = v;
            v = v->child_[r+1]; 
        }
        // 失败
        return nullptr;
    }

    // 插入
    bool insert(const T& s){
        // e 存在则直接返回
        auto v = search(e);
        if(v) {
            return false;
        }
        // 在hot_的有序关键码查找合适的插入位置
        auto r = hot_->key_.search(r+1, e);
        // 插入新关键码
        hot_->key_.insert(r+1, e);
        // 如有必要则分裂
        solveOverflow(hot_);
        return true;
    }

    // 删除
    // 若是叶节点则直接删除，若不是则与直接后继互换位置后删除(直接后继必为一个叶节点)
    bool remove(const T& e){
        auto v = search(e);
        // 查看关键码是否存在
        if(!v) { return false;}
        // 找到关键码的位置
        auto r = v->key_.search(e);
        // 若v非叶子，则e的直接后继必属于某叶子节点
        // 与直接后继互换位置
        if(v->child_[0]){
            auto u = v->child_[r+1];
            while(u->child_[0]){ u = u->child_[0];}
            v->key_[r] = u->key_[0];
            v = u;
            r = 0;
        }
        // 删除关键码，及其两个外部节点之一(key 与 value 数量相差 1 )
        v->key_.remove(r);
        v->child_.remove(r+1);
        N_--;
        // 处理上溢情况
        solveUnderflow(v);
        return true;
    }
};



}


#endif //  _DSA_INCLUDE_SRC_BTREE_H__
