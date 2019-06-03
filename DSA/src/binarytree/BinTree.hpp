#ifndef CODE_DIARY_DSA_SRC_BINTREE_H__
#define CODE_DIARY_DSA_SRC_BINTREE_H__

#include<algorithm>
#include"BinNode.hpp"
#include"../_share/comparator.h"
#include"../_share/release.h"
template<typename T> 
class BinTree{
protected:
    // 规模
    int _size;
    // 根节点
    BinNodePosi(T) _root;
    // 更新节点x的高度
    // 对于不同种类的二叉树，高度定义也可能不同
    virtual int updateHeight(BinNodePosi(T) x);
    // 更新节点x及其祖先的高度
    void updateHeightAbove(BinNodePosi(T) x);
public:
    // 构造函数
    BinTree() : _size(0),_root(nullptr){}
    // 析构函数
    ~BinTree(){if(0<_size) remove(_root);}
    // 规模
    int size() const{return _size;}
    // 判断是否为空
    bool empty() const{return !_root;}
    // 根
    BinNodePosi(T) root() const {return _root;}
    // 插入根节点
    BinNodePosi(T) insertAsRoot(T const& e);
    // e作为x左子节点插入（原来无）
    BinNodePosi(T) insertAsLChild(BinNodePosi(T) x,T const& e);
    // e作为x右子节点插入（原来无）
    BinNodePosi(T) insertAsRChild(BinNodePosi(T) x,T const& e);
    // Tree作为x左子树接入
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &Tree);
    // Tree作为x右子树接入
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &Tree);
    // 删除以x为根节点的子树
    int remove(BinNodePosi(T) x);
    // 将子树x从当前树中摘除，并转换为一棵新的树
    BinTree<T>* secede(BinNodePosi(T) x);
    // 层次遍历
    template<typename VST>
    void travLevel(VST& visit){ if(_root) _root->travLevel(visit);}
    // 先序遍历
    template<typename VST>
    void travPre(VST& visit){ if(_root) _root->travPre(visit);}
    // 中序遍历
    template<typename VST>
    void travIn(VST& visit){ if(_root) _root->travIn(visit);}
    // 后序遍历
    template<typename VST>
    void travPost(VST& visit){ if(_root) _root->travPost(visit);}
    // 比较器
    bool operator<(BinTree<T> const& t){
        return _root && t._root && comparator::lt(_root,t._root);//lt(_root,t._root);
    }
    // 判等器
    bool operator==(BinTree<T> const& t){
        return _root && t._root && (_root == t._root);
    }

}; // BinTree

//  更新节点x的高度
template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x){
    return x->height = 1 + std::max(stature(x->lc),stature(x->rc));
}
//  更新节点x及其祖先高度
template<typename T> 
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x){
    while(x){
        updateHeight(x);
        x = x->parent;
    }
}

//  节点插入
// 将e当成根节点插入空的二叉树
template<typename T> 
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e){
    _size = 1;
    return _root = new BinTree<T> (e);
}

// 插入e为左孩子
template<typename T> 
BinNodePosi(T) BinTree<T>::insertAsLChild(BinNodePosi(T) x,T const& e){
    ++ _size;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

// 插入e为右孩子
template<typename T> 
BinNodePosi(T) BinTree<T>::insertAsRChild(BinNodePosi(T) x,T const& e){
    ++ _size;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

// 子树的接入
// 将子树Tree作为节点x的子树，S本身置空
template<typename T> 
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &Tree){
    if(x->lc = Tree->root) 
        x->lc->parent = x;
    _size += Tree->size;
    updateHeightAbove(x);
    Tree->_root = nullptr;
    Tree->_size = 0;
    release::release(Tree);
    Tree = nullptr;
    return x;
}

template<typename T> 
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &Tree){
    if(x->rc = Tree->root) 
        x->rc->parent = x;
    _size += Tree->size;
    updateHeightAbove(x);
    Tree->_root = nullptr;
    Tree->_size = 0;
    release::release(Tree);
    Tree = nullptr;
    return x;
}



#endif // CODE_DIARY_DSA_SRC_BINTREE_H__ 